#!/usr/bin/env python
# coding: utf-8

import os, sys, md5, re, json, pdb
from pprint import pprint as pp
from gx_gltf_make import Gltf, DagTree, gxDagTree

builtin = re.compile("""^#<BUILTIN>\\s*(.*)\\s*=\\s*(.*)\\s*$""", re.MULTILINE)

class QtGpuMesh:
    template = """
    class gxGpuMesh_%%gen_signature%%: public QObject, protected QOpenGlFunctions
    {
        QOBJECT
    public slots:
        %%gen_public_slots%%
    };
    """
    glsl_vertex_attribute = dict(
        P3 = ( 'vec4' , 'a_position'  , 'QVector3D' ),
        N3 = ( 'vec4' , 'a_normal'    , 'QVector3D' ),
        T2 = ( 'vec2' , 'a_texCoord0' , 'QVector2D' ),
    )
    attributes = []
    slots = []
    def __init__(self):
        print("++%s" % self)
    
    def __del__(self):
        print("--%s" % self)
    
    def generate(self, here):
        here.get_name()
        
    def pprint(self, out = sys.stdout):
        out.write("Hello .pprint Method%s" % self)
    
    def gen_signature(self):
        return "/*GEN SIGNATURE*/"

    def gen_public_slots(self):
        buff = "//GEN PUBLIC SLOTS BEGIN\n"
        for i in self.slots:
            buff += i.generate(self)
        buff+= "//GEN PUBLIC SLOTS END\n"
        return buff


def generate_from_file( NAME, PATH, PWD ):
    PATH = os.path.normpath(os.path.abspath(PATH))
    print("%s for %s" % (NAME, PWD) )
    if not os.path.isfile(PATH):
        print("  GENERATE: ERROR: FILE NOT FOUND '%s'" % (PATH))
        return
    gltf = Gltf(PATH)
    dag  = DagTree(gltf)
    gxt  = gxDagTree(dag)
    print("  skin count %d" % len(gltf.skins))
    print("  mesh count %d" % len(gltf.meshes))
    print("  mtrl count %d" % len(gltf.materials))
    mesh_keys = set(gxt.get_mesh_keys())
    for i in mesh_keys:
        vertex_attributes =  gxt.get_mesh_attributes(i)
        method_name = 'get_interleaved_'
        mode = ('mesh', 'skin') [ u'WEIGHTS_0' in vertex_attributes ]
        print("  %s[%s] %s %s" % (mode, i, gxt.get_mesh_name(i), vertex_attributes))
        if u'POSITION'   in vertex_attributes: method_name += 'P3'
        if u'NORMAL'     in vertex_attributes: method_name += 'N3'
        if u'WEIGHTS_0'  in vertex_attributes: method_name += 'W4'
        if u'JOINTS_0'   in vertex_attributes: method_name += 'J4'
        if u'TEXCOORD_0' in vertex_attributes: method_name += 'T2'
        print("          %s" % method_name)
        method = getattr(gxt, method_name)
        vertices, vbo = method(i)
        indices,  ibo = gxt.get_indices_PP()
    print()

def generate(PWD, CWD, PRO, SRC):
    print(PWD)
    print(CWD)
    print(PRO)
    builtins = dict([ match.groups() for match in re.finditer(builtin, SRC) ])
    pp(builtins, width=1)
    for project_name in sorted(builtins.keys()):
        name = project_name
        path = builtins[project_name]
        generate_from_file(name, path, PWD)
    print()

def main(sources_dir, project_dir, rebuild_all = False):

    # WHERE IS QMAKE(META OBJECT COMPILER) PROJECT-FILE CALLED THIS GENERATOR
    PWD    = project_dir
    print("PWD    = %s"%PWD)

    # WHERE IS THIS FILE's PARENT FOLDER
    CWD    = sources_dir
    print("CWD    = %s"%CWD)

    # ONLY ONE '.pro' FILE SUPPORTED
    PRO    = os.path.join(PWD, [ i for i in os.listdir(PWD) if i.endswith(".pro") ][0] )
    print("PRO    = %s"%PRO)

    # READ '.pro' FILE
    SRC    = open(PRO,"r").read()

    # for i in os.listdir(PWD): print(i)

    # COMPUTE '.pro' FILE MD5
    MD5    = md5.new(SRC).hexdigest()

    # TRY TO EXTRACT STORED_MD5
    STORED_MD5 = ''
    try:
        with open(PRO+".builtins", "r") as f:
            STORED_MD5 = json.loads(f.read())['MD5']
    except IOError   :
        print("GENERATE: '.builtins' file not found")
    except KeyError  :
        print("GENERATE, 'md5' not stored in '.builtins' file")
    except ValueError:
        print("GENERATE, '.builtins' file invalid")

    # COMPARE CURRENT MD5 WITH STORED_MD5
    if STORED_MD5 == MD5:
        if rebuild_all:
            print("GENERATE: MD5 ARE EQUAL, BUT rebuild_all == True")
        else:
            print("GENERATE: MD5 ARE EQUAL, SKIPPED")
            return

    print("GENERATE BEGIN")
    session = dict()
    session['MD5'] = MD5
    session['PWD'] = PWD
    session['CWD'] = CWD

    generate( PWD, CWD, PRO, SRC )

    with open(PRO+".builtins", "w") as f:
        f.write(json.dumps(session, sort_keys=True, indent=4, separators=(',', ':')))

    print("GENERATE END")

if __name__ == '__main__':

    if len(sys.argv) == 1:
        rebuild = True                      # TEST/DEBUG CASE force rebuild.
        sys.argv.append("../gx_qt5_cube")   # SO, IS TEST/DEBUG CASE.
    else:
        rebuild = False

    sources_dir = os.path.normpath(os.path.split(os.path.abspath(sys.argv[0]))[0])
    project_dir = os.path.normpath(os.path.abspath(sys.argv[1]))
    main( sources_dir, project_dir, rebuild )

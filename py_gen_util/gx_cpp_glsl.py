import sys

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
    
    def generate(self, context):
        context.get_name()
        
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

if __name__ =='__main__':
    class QtGpuMeshContext:
        def get_name(self): return '/*UNDEFINED GET NAME*/'
    context = QtGpuMeshContext()
    test = QtGpuMesh()
    test.generate(context)
    test.pprint()
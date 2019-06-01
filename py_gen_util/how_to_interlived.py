

def interlived(a,b):
    head = "".join(["".join(i) for i in zip(a,b)])
    size = len(head)/2
    if len(a) == size:
        return head+b[size:]
    return head+a[size:]


if __name__ == '__main__':
    ts = interlived("abcdef","123")
    te = interlived("abcdef", "123456")
    tl = interlived("abcdef", "123456890")
    print("\n")
   
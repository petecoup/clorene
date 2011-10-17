def embed_file_as_string(infile, outfile):
    in_f = open(infile, 'r')
    out_f = open(outfile, 'w')

    lines = in_f.readlines()

    out_f.write('const char* OPENCL_STDHEADER =\n');

    for line in lines:
#        out_f.write('LL:%s' % (len(line),))
        for i in range(len(line)):
            if (i % 10 == 0):
                out_f.write('"')
            v = hex(ord(line[i]))
            out_f.write('\\%s' % (v[1:],))
            if (i % 10 == 9):
                out_f.write('"\n')
        if len(line) % 10 != 0:
            out_f.write('"')
        out_f.write('\n')

    out_f.write(';\n')
    in_f.close()
    out_f.close()

if __name__=='__main__':
    import sys
    embed_file_as_string(sys.argv[1], sys.argv[2])


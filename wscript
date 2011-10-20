import os

POCO_ROOT = os.environ['POCO_ROOT']

memory_srcs = ['MemoryObject.cpp',
               'MemoryObjectFactory.cpp',
               'Buffer.cpp']
command_queue_srcs = ['CommandQueue.cpp',
                      'CommandQueueFactory.cpp',
                      'NDRangeKernel.cpp',
                      'ReadBuffer.cpp',
                      'WriteBuffer.cpp']
base_srcs = ['api.cpp',
             'Context.cpp',
             'ContextFactory.cpp',
             'Device.cpp',
             'Platform.cpp']
program_srcs = ['Compiler.cpp',
                'Program.cpp',
                'ProgramFactory.cpp',
                'Kernel.cpp']
runtime_srcs = ['Engine.cpp',
                'Runtime.cpp',
                'FunctionRunner.cpp',
                'Worker.cpp']
unittest_srcs = ['api_full.cpp',
                 'common_functions.cpp',
                 'driver.cpp',
                 'memory.cpp',
                 'simple_builtin.cpp',
                 'simple_floatvec.cpp',
                 'simple_full.cpp']

platform_srcs = ['CommonFunctions']

clang_libs_list = ['clangFrontendTool',
                   'clangFrontend',
                   'clangDriver',
                   'clangSerialization',
                   'clangCodeGen',
                   'clangParse',
                   'clangSema',
                   'clangStaticAnalyzerFrontend',
                   'clangStaticAnalyzerCheckers',
                   'clangStaticAnalyzerCore',
                   'clangAnalysis',
                   'clangIndex',
                   'clangRewrite',
                   'clangAST',
                   'clangLex',
                   'clangBasic']


llvm_packages = ['jit',
                 'ipo',
                 'instrumentation',
                 'interpreter',
                 'asmparser',
                 'core',
                 'codegen',
                 'bitreader',
                 'bitwriter',
                 'linker',
                 'native']

def options(opt):
    opt.load('compiler_cxx')

def configure(cnf):
    cnf.load('compiler_cxx')
    cnf.check_cfg(path='llvm-config', 
                  args='--cxxflags --ldflags --libs',
                  package=' '.join(llvm_packages),
                  uselib_store='LLVM')
    cnf.env['CXXFLAGS_LLVM'].remove('-fno-exceptions')
    cnf.env['CXXFLAGS_LLVM'].remove('-fno-rtti')

def build(bld):
    src_list = ' memory/'+' memory/'.join(memory_srcs) + \
               ' command_queue/'+' command_queue/'.join(command_queue_srcs) + \
               ' '+' '.join(base_srcs) + \
               ' program/'+' program/'.join(program_srcs) + \
               ' runtime/'+' runtime/'.join(runtime_srcs)

    unittest_list = ' test/unit/'+' test/unit/'.join(unittest_srcs)

    # make the embedded PlatformStdlib.opencl.h header.
    obj = bld(rule='python ${SRC} ${TGT}',
              source='tools/embed_file_as_string.py platform/PlatformStdlib.h',
              target='platform/PlatformStdlib.opencl.h')

    bc_list = []
    for s in platform_srcs:
        obj = bld(rule='clang ${SRC} -c -emit-llvm -o ${TGT}',
                  source='platform/'+s+'.cl', target=s+'.bc')
        bc_list.append(s+'.bc')

    obj = bld(rule='llvm-ld -link-as-library -o ${TGT} ${SRC}',
              source=bc_list, target='stdlib.bc')
        
    obj = bld(features='cxx cxxshlib',
              source=src_list,
              target='OpenCL',
              includes=POCO_ROOT + '/include include .',
              cxxflags='-Wall -g',
              lib=clang_libs_list + ['PocoFoundation'],
              libpath=[POCO_ROOT + '/lib'],
              use='LLVM')

    obj = bld(features='cxx cxxprogram',
              source=unittest_list,
              target='clorene_test',
              includes='include .',
              lib=['gtest', 'PocoFoundation'],
              libpath=[POCO_ROOT + '/lib'],
              use='OpenCL')


/*
 * Copyright (C) 2011 Peter Couperus
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <iostream>

#include <llvm/Support/Path.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Support/Host.h>
#include <llvm/Module.h>
#include <llvm/Linker.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Basic/TargetInfo.h>

#include "Program.h"
#include "Kernel.h"
#include "Compiler.h"
#include "platform/PlatformStdlib.opencl.h"


namespace clorene
{

Compiler::Compiler()
{
    init();
}

Compiler::~Compiler()
{
}

void
Compiler::init()
{
    clang_ = new clang::CompilerInstance();
    clang_->createFileManager();

    llvm::raw_fd_ostream stderrRaw(2, false);
    clang::TextDiagnosticPrinter* diagPrinter =
        new clang::TextDiagnosticPrinter(stderrRaw, clang::DiagnosticOptions());
    clang_->createDiagnostics(0, NULL, diagPrinter);

    clang::TargetOptions& targetOpts = clang_->getTargetOpts();
    targetOpts.Triple = llvm::sys::getHostTriple();

    clang_->getInvocation().setLangDefaults(clang::IK_OpenCL);
}

llvm::Module*
Compiler::compile(const std::string& program_)
{
    std::string header(OPENCL_STDHEADER);

    std::string prf = header + program_;

    llvm::MemoryBuffer* bufptr
        = llvm::MemoryBuffer::getMemBuffer(prf);

    clang::FrontendOptions& frontend = clang_->getFrontendOpts();
    frontend.Inputs.push_back(
        std::make_pair(clang::IK_OpenCL, "_tmp.cl"));

    clang::PreprocessorOptions& preprocessor = clang_->getPreprocessorOpts();
    preprocessor.addRemappedFile("_tmp.cl", bufptr);

    clang::CodeGenAction* action = new clang::EmitLLVMOnlyAction();
    if (clang_->ExecuteAction(*action)) {
        llvm::Module* result = action->takeModule();

        // now, link in the stdlib.
        llvm::Linker linker("program", result);

        bool native;
        llvm::sys::Path mypath;
        mypath.set("stdlib.bc");

        //Linker returns false on success.
        if (!linker.LinkInFile(mypath, native)) {
            result = linker.releaseModule();
        } else {
            //Error in linking.
            std::cerr << "Error linking module." << std::endl;
        }

        return result;
    }

    return 0;
}

}


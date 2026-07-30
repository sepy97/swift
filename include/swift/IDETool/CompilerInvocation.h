//===--- CompilerInvocation.h ---------------------------------------------===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2022 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_IDE_COMPILERINVOCATION_H
#define SWIFT_IDE_COMPILERINVOCATION_H

#include "swift/Frontend/Frontend.h"

namespace swift {

class CompilerInvocation;

namespace ide {

bool initCompilerInvocation(
    CompilerInvocation &Invocation, ArrayRef<const char *> OrigArgs,
    FrontendOptions::ActionType Action, DiagnosticEngine &Diags,
    StringRef UnresolvedPrimaryFile,
    llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> FileSystem,
    const std::string &swiftExecutablePath,
    const std::string &runtimeResourcePath, time_t sessionTimestamp,
    std::string &Error);

/// Initializes \p Invocation from *frontend* arguments (i.e. arguments for
/// 'swift-frontend'), rather than the driver arguments taken by
/// \c initCompilerInvocation.
///
/// No driver is involved: the arguments are parsed directly. This is the entry
/// point for clients that can supply the frontend command line a real compile
/// would use — in particular one built with explicit modules, whose flags (e.g.
/// '-explicit-swift-module-map-file') are frontend-only and so cannot be
/// expressed in driver arguments, nor derived from them by the driver.
///
/// The same SourceKit-specific policy is applied as on the driver-argument
/// path, so features behave identically regardless of which entry point was
/// used. In particular the invocation produces no build products, whatever
/// output flags \p OrigArgs carried.
///
/// \param OrigArgs Frontend arguments. A leading '-frontend' is accepted and
/// ignored, so a frontend job's argument list may be passed verbatim.
/// \param UnresolvedPrimaryFile If non-empty, designates the primary input, and
/// any '-primary-file' in \p OrigArgs is ignored. If empty, \p OrigArgs must
/// designate at most one primary.
///
/// \returns True on error, and sets \p Error.
bool initCompilerInvocationFromFrontendArgs(
    CompilerInvocation &Invocation, ArrayRef<const char *> OrigArgs,
    FrontendOptions::ActionType Action, DiagnosticEngine &Diags,
    StringRef UnresolvedPrimaryFile,
    llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> FileSystem,
    const std::string &swiftExecutablePath,
    const std::string &runtimeResourcePath, time_t sessionTimestamp,
    std::string &Error);

bool initInvocationByClangArguments(ArrayRef<const char *> ArgList,
                                    CompilerInvocation &Invok,
                                    std::string &Error);

} // namespace ide
} // namespace swift

#endif // SWIFT_IDE_COMPILERINVOCATION_H

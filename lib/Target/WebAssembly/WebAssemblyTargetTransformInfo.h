//==- WebAssemblyTargetTransformInfo.h - WebAssembly-specific TTI -*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief This file a TargetTransformInfo::Concept conforming object specific
/// to the WebAssembly target machine.
///
/// It uses the target's detailed information to provide more precise answers to
/// certain TTI queries, while letting the target independent and default TTI
/// implementations handle the rest.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_WEBASSEMBLY_WEBASSEMBLYTARGETTRANSFORMINFO_H
#define LLVM_LIB_TARGET_WEBASSEMBLY_WEBASSEMBLYTARGETTRANSFORMINFO_H

#include "WebAssemblyTargetMachine.h"
#include "llvm/CodeGen/BasicTTIImpl.h"
#include <algorithm>

namespace llvm {

class WebAssemblyTTIImpl final : public BasicTTIImplBase<WebAssemblyTTIImpl> {
  typedef BasicTTIImplBase<WebAssemblyTTIImpl> BaseT;
  typedef TargetTransformInfo TTI;
  friend BaseT;

  const WebAssemblyTargetMachine *TM;
  const WebAssemblySubtarget *ST;
  const WebAssemblyTargetLowering *TLI;

  const WebAssemblySubtarget *getST() const { return ST; }
  const WebAssemblyTargetLowering *getTLI() const { return TLI; }

public:
  WebAssemblyTTIImpl(const WebAssemblyTargetMachine *TM, Function &F)
      : BaseT(TM), TM(TM), ST(TM->getSubtargetImpl(F)),
        TLI(ST->getTargetLowering()) {}

  // Provide value semantics. MSVC requires that we spell all of these out.
  WebAssemblyTTIImpl(const WebAssemblyTTIImpl &Arg)
      : BaseT(static_cast<const BaseT &>(Arg)), TM(Arg.TM), ST(Arg.ST),
        TLI(Arg.TLI) {}
  WebAssemblyTTIImpl(WebAssemblyTTIImpl &&Arg)
      : BaseT(std::move(static_cast<BaseT &>(Arg))), TM(std::move(Arg.TM)),
        ST(std::move(Arg.ST)), TLI(std::move(Arg.TLI)) {}
  WebAssemblyTTIImpl &operator=(const WebAssemblyTTIImpl &RHS) {
    BaseT::operator=(static_cast<const BaseT &>(RHS));
    TM = RHS.TM;
    ST = RHS.ST;
    TLI = RHS.TLI;
    return *this;
  }
  WebAssemblyTTIImpl &operator=(WebAssemblyTTIImpl &&RHS) {
    BaseT::operator=(std::move(static_cast<BaseT &>(RHS)));
    TM = std::move(RHS.TM);
    ST = std::move(RHS.ST);
    TLI = std::move(RHS.TLI);
    return *this;
  }

  /// \name Scalar TTI Implementations
  /// @{

  // TODO: Implement more Scalar TTI for WebAssembly

  TTI::PopcntSupportKind getPopcntSupport(unsigned TyWidth);

  /// @}

  /// \name Vector TTI Implementations
  /// @{

  // TODO: Implement Vector TTI for WebAssembly

  /// @}
};

} // end namespace llvm

#endif

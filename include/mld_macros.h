#ifndef MLD_INCLUDE_MLD_MACROS_H
#define MLD_INCLUDE_MLD_MACROS_H

#if defined(__cplusplus)
#define MLD_START_CPP_NAMESPACE \
    namespace mld {             \
    extern "C" {
#define MLD_END_CPP_NAMESPACE \
    }                        \
    }
#else
#define MLD_START_CPP_NAMESPACE
#define MLD_END_CPP_NAMESPACE
#endif

#endif  // MLD_INCLUDE_MLD_MACROS_H

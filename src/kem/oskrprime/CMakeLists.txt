set(_OSKRPRIME_OBJS "")


if(OQS_ENABLE_KEM_oskrprime_538)
    add_library(oskrprime_538 OBJECT kem_oskrprime_538.c OSKR-Prime-538/kem.c OSKR-Prime-538/indcpa.c OSKR-Prime-538/polyvec.c OSKR-Prime-538/poly.c OSKR-Prime-538/ntt.c OSKR-Prime-538/cbd.c OSKR-Prime-538/reduce.c OSKR-Prime-538/verify.c OSKR-Prime-538/fips202.c OSKR-Prime-538/symmetric-shake.c OSKR-Prime-538/randombytes.c) #这里不能够有斜杠
    #target_compile_options(oskrprime_538 PUBLIC -DOSKR_K=2)
    target_include_directories(oskrprime_538 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/OSKR-Prime-538)
    set(_OSKRPRIME_OBJS ${_OSKRPRIME_OBJS} $<TARGET_OBJECTS:oskrprime_538>)
endif()

set(OSKRPRIME_OBJS ${_OSKRPRIME_OBJS} PARENT_SCOPE)


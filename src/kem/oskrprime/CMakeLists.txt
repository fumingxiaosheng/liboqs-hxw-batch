set(_OSKRPRIME_OBJS "")


if(OQS_ENABLE_KEM_oskrprime_538)
    add_library(oskrprime_538 OBJECT kem_oskrprime_538.c OSKR-Prime-538/kem.c OSKR-Prime-538/indcpa.c OSKR-Prime-538/polyvec.c OSKR-Prime-538/poly.c OSKR-Prime-538/ntt.c OSKR-Prime-538/cbd.c OSKR-Prime-538/reduce.c OSKR-Prime-538/verify.c OSKR-Prime-538/fips202.c OSKR-Prime-538/symmetric-shake.c OSKR-Prime-538/randombytes.c) #这里不能够有斜杠
    #target_compile_options(oskrprime_538 PUBLIC -DOSKR_K=2)
    target_include_directories(oskrprime_538 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/OSKR-Prime-538)
    set(_OSKRPRIME_OBJS ${_OSKRPRIME_OBJS} $<TARGET_OBJECTS:oskrprime_538>)
endif()

if(OQS_ENABLE_KEM_oskrprime_771)
    add_library(oskrprime_771 OBJECT kem_oskrprime_771.c OSKR-Prime-771/kem.c OSKR-Prime-771/indcpa.c OSKR-Prime-771/polyvec.c OSKR-Prime-771/poly.c OSKR-Prime-771/ntt.c OSKR-Prime-771/cbd.c OSKR-Prime-771/reduce.c OSKR-Prime-771/verify.c OSKR-Prime-771/fips202.c OSKR-Prime-771/symmetric-shake.c OSKR-Prime-771/randombytes.c) #这里不能够有斜杠
    #target_compile_options(oskrprime_771 PUBLIC -DOSKR_K=2)
    target_include_directories(oskrprime_771 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/OSKR-Prime-771)
    set(_OSKRPRIME_OBJS ${_OSKRPRIME_OBJS} $<TARGET_OBJECTS:oskrprime_771>)
endif()


if(OQS_ENABLE_KEM_oskrprime_807)
    add_library(oskrprime_807 OBJECT kem_oskrprime_807.c OSKR-Prime-807/kem-807.c OSKR-Prime-807/indcpa-807.c OSKR-Prime-807/polyvec-807.c OSKR-Prime-807/poly-807.c OSKR-Prime-807/ntt-807.c OSKR-Prime-807/cbd-807.c OSKR-Prime-807/reduce-807.c OSKR-Prime-807/verify-807.c OSKR-Prime-807/fips202-807.c OSKR-Prime-807/symmetric-shake-807.c OSKR-Prime-807/randombytes-807.c) #这里不能够有斜杠
    #target_compile_options(oskrprime_538 PUBLIC -DOSKR_K=2)
    target_include_directories(oskrprime_807 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/OSKR-Prime-807)
    set(_OSKRPRIME_OBJS ${_OSKRPRIME_OBJS} $<TARGET_OBJECTS:oskrprime_807>)
endif()

if(OQS_ENABLE_KEM_oskrprime_1076)
    add_library(oskrprime_1076 OBJECT kem_oskrprime_1076.c OSKR-Prime-1076/kem.c OSKR-Prime-1076/indcpa.c OSKR-Prime-1076/polyvec.c OSKR-Prime-1076/poly.c OSKR-Prime-1076/ntt.c OSKR-Prime-1076/cbd.c OSKR-Prime-1076/reduce.c OSKR-Prime-1076/verify.c OSKR-Prime-1076/fips202.c OSKR-Prime-1076/symmetric-shake.c OSKR-Prime-1076/randombytes.c) #这里不能够有斜杠
    #target_compile_options(oskrprime_1076 PUBLIC -DOSKR_K=2)
    target_include_directories(oskrprime_1076 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/OSKR-Prime-1076)
    set(_OSKRPRIME_OBJS ${_OSKRPRIME_OBJS} $<TARGET_OBJECTS:oskrprime_1076>)
endif()

if(OQS_ENABLE_KEM_oskrprime_1142)
    add_library(oskrprime_1142 OBJECT kem_oskrprime_1142.c OSKR-Prime-1142/kem.c OSKR-Prime-1142/indcpa.c OSKR-Prime-1142/polyvec.c OSKR-Prime-1142/poly.c OSKR-Prime-1142/ntt.c OSKR-Prime-1142/cbd.c OSKR-Prime-1142/reduce.c OSKR-Prime-1142/verify.c OSKR-Prime-1142/fips202.c OSKR-Prime-1142/symmetric-shake.c OSKR-Prime-1142/randombytes.c) #这里不能够有斜杠
    #target_compile_options(oskrprime_1142 PUBLIC -DOSKR_K=2)
    target_include_directories(oskrprime_1142 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/OSKR-Prime-1142)
    set(_OSKRPRIME_OBJS ${_OSKRPRIME_OBJS} $<TARGET_OBJECTS:oskrprime_1142>)
endif()

set(OSKRPRIME_OBJS ${_OSKRPRIME_OBJS} PARENT_SCOPE)


set(_FPTRU_OBJS "")


if(OQS_ENABLE_KEM_fptru_761)
    message("huxiaowen 761")
    add_library(fptru_761 OBJECT kem_fptru_761.c fptru_main/poly_mul_n761q/radix_ntt_n761.c fptru_main/cbd.c fptru_main/coding.c fptru_main/cpucycles.c fptru_main/fips202.c fptru_main/inverse.c fptru_main/kem.c fptru_main/pack.c fptru_main/pke.c fptru_main/poly.c fptru_main/randombytes.c fptru_main/reduce.c fptru_main/speed.c) #这里不能够有斜杠
    target_compile_options(fptru_761 PUBLIC -DFPTRU_N=761)
    target_include_directories(fptru_761 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_main)
    target_include_directories(fptru_761 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_main/poly_mul_n761q)
    set(_FPTRU_OBJS ${_FPTRU_OBJS} $<TARGET_OBJECTS:fptru_761>)
endif()

if(OQS_ENABLE_KEM_fptru_653)
    add_library(fptru_653 OBJECT kem_fptru_653.c fptru_653/poly_mul_n653q/radix_ntt_n653.c fptru_653/cbd.c fptru_653/coding.c fptru_653/cpucycles.c fptru_653/fips202.c fptru_653/inverse.c fptru_653/kem.c fptru_653/pack.c fptru_653/pke.c fptru_653/poly.c fptru_653/randombytes.c fptru_653/reduce.c fptru_653/speed.c) #这里不能够有斜杠
    target_compile_options(fptru_653 PUBLIC -DFPTRU_N=653)
    target_include_directories(fptru_653 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_653)
    target_include_directories(fptru_653 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_653/poly_mul_n653q)
    set(_FPTRU_OBJS ${_FPTRU_OBJS} $<TARGET_OBJECTS:fptru_653>)
endif()

set(FPTRU_OBJS ${_FPTRU_OBJS} PARENT_SCOPE)
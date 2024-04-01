set(_FPTRU_OBJS "")


if(OQS_ENABLE_KEM_fptru_653)
    add_library(fptru_653 OBJECT kem_fptru_653.c fptru_653/poly_mul_n653q/radix_ntt_n653.c fptru_653/cbd.c fptru_653/coding.c fptru_653/cpucycles.c fptru_653/fips202.c fptru_653/inverse.c fptru_653/kem.c fptru_653/pack.c fptru_653/pke.c fptru_653/poly.c fptru_653/randombytes.c fptru_653/reduce.c fptru_653/speed.c) #这里不能够有斜杠
    target_compile_options(fptru_653 PUBLIC -DFPTRU_N=653)
    target_include_directories(fptru_653 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_653)
    target_include_directories(fptru_653 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_653/poly_mul_n653q)
    set(_FPTRU_OBJS ${_FPTRU_OBJS} $<TARGET_OBJECTS:fptru_653>)
endif()

set(FPTRU_OBJS ${_FPTRU_OBJS} PARENT_SCOPE)
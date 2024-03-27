set(_FPTRU_OBJS "")
# uodate

if(OQS_ENABLE_KEM_fptru_653)
    add_library(fptru_653 OBJECT kem_fptru_653.c fptru_main/poly_mul_n653q/radix_ntt_n653.c fptru_main/cbd.c fptru_main/coding.c fptru_main/cpucycles.c fptru_main/fips202.c fptru_main/inverse.c fptru_main/kem.c fptru_main/pack.c fptru_main/pke.c fptru_main/poly.c fptru_main/randombytes.c fptru_main/reduce.c fptru_main/speed.c) #这里不能够有斜杠
    target_compile_options(fptru_653 PUBLIC -DFPTRU_N=653)
    target_include_directories(fptru_653 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_main)
    target_include_directories(fptru_653 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_main/poly_mul_n653q)
    set(_FPTRU_OBJS ${_FPTRU_OBJS} $<TARGET_OBJECTS:fptru_653>)
endif()

if(OQS_ENABLE_KEM_fptru_761)
    add_library(fptru_761 OBJECT kem_fptru_761.c fptru_main/poly_mul_n761q/radix_ntt_n761.c fptru_main/cbd.c fptru_main/coding.c fptru_main/cpucycles.c fptru_main/fips202.c fptru_main/inverse.c fptru_main/kem.c fptru_main/pack.c fptru_main/pke.c fptru_main/poly.c fptru_main/randombytes.c fptru_main/reduce.c fptru_main/speed.c) #这里不能够有斜杠
    target_compile_options(fptru_761 PUBLIC -DFPTRU_N=761)
    target_include_directories(fptru_761 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_main)
    target_include_directories(fptru_761 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_main/poly_mul_n761q)
    set(_FPTRU_OBJS ${_FPTRU_OBJS} $<TARGET_OBJECTS:fptru_761>)
endif()

if(OQS_ENABLE_KEM_fptru_1277)
    add_library(fptru_1277 OBJECT kem_fptru_1277.c fptru_main/poly_mul_n1277q/radix_ntt_n1277.c fptru_main/cbd.c fptru_main/coding.c fptru_main/cpucycles.c fptru_main/fips202.c fptru_main/inverse.c fptru_main/kem.c fptru_main/pack.c fptru_main/pke.c fptru_main/poly.c fptru_main/randombytes.c fptru_main/reduce.c fptru_main/speed.c) #这里不能够有斜杠
    target_compile_options(fptru_1277 PUBLIC -DFPTRU_N=1277)
    target_include_directories(fptru_1277 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_main)
    target_include_directories(fptru_1277 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_main/poly_mul_n1277q)
    set(_FPTRU_OBJS ${_FPTRU_OBJS} $<TARGET_OBJECTS:fptru_1277>)
endif()

set(FPTRU_OBJS ${_FPTRU_OBJS} PARENT_SCOPE)
set(_FPTRU_OBJS "")


if(OQS_ENABLE_KEM_fptru_653_batch)
    add_library(fptru_653_batch OBJECT kem_fptru_653_batch.c fptru_653_batch/poly_mul_n653q/radix_ntt_n653.c fptru_653_batch/cbd.c fptru_653_batch/coding.c fptru_653_batch/cpucycles.c fptru_653_batch/fips202.c fptru_653_batch/inverse.c fptru_653_batch/kem.c fptru_653_batch/pack.c fptru_653_batch/pke.c fptru_653_batch/poly.c fptru_653_batch/randombytes.c fptru_653_batch/reduce.c fptru_653_batch/speed.c) #这里不能够有斜杠
    target_compile_options(fptru_653_batch PUBLIC -DFPTRU_N=653)
    target_include_directories(fptru_653_batch PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_653_batch)
    target_include_directories(fptru_653_batch PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_653_batch/poly_mul_n653q)
    set(_FPTRU_OBJS ${_FPTRU_OBJS} $<TARGET_OBJECTS:fptru_653_batch>)
endif()

if(OQS_ENABLE_KEM_fptru_761_batch)
    add_library(fptru_761_batch OBJECT kem_fptru_761_batch.c fptru_761_batch/poly_mul_n761q/radix_ntt_n761.c fptru_761_batch/cbd.c fptru_761_batch/coding.c fptru_761_batch/cpucycles.c fptru_761_batch/fips202.c fptru_761_batch/inverse.c fptru_761_batch/kem.c fptru_761_batch/pack.c fptru_761_batch/pke.c fptru_761_batch/poly.c fptru_761_batch/randombytes.c fptru_761_batch/reduce.c fptru_761_batch/speed.c) #这里不能够有斜杠
    target_compile_options(fptru_761_batch PUBLIC -DFPTRU_N=761)
    target_include_directories(fptru_761_batch PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_761_batch)
    target_include_directories(fptru_761_batch PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_761_batch/poly_mul_n761q)
    set(_FPTRU_OBJS ${_FPTRU_OBJS} $<TARGET_OBJECTS:fptru_761_batch>)
endif()

if(OQS_ENABLE_KEM_fptru_1277_batch)
    add_library(fptru_1277_batch OBJECT kem_fptru_1277_batch.c fptru_1277_batch/poly_mul_n1277q/radix_ntt_n1277.c fptru_1277_batch/cbd.c fptru_1277_batch/coding.c fptru_1277_batch/cpucycles.c fptru_1277_batch/fips202.c fptru_1277_batch/inverse.c fptru_1277_batch/kem.c fptru_1277_batch/pack.c fptru_1277_batch/pke.c fptru_1277_batch/poly.c fptru_1277_batch/randombytes.c fptru_1277_batch/reduce.c fptru_1277_batch/speed.c) #这里不能够有斜杠
    target_compile_options(fptru_1277_batch PUBLIC -DFPTRU_N=1277)
    target_include_directories(fptru_1277_batch PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_1277_batch)
    target_include_directories(fptru_1277_batch PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_1277_batch/poly_mul_n1277q)
    set(_FPTRU_OBJS ${_FPTRU_OBJS} $<TARGET_OBJECTS:fptru_1277_batch>)
endif()

if(OQS_ENABLE_KEM_fptru_653)
    add_library(fptru_653 OBJECT kem_fptru_653.c fptru_653/poly_mul_n653q/radix_ntt_n653.c fptru_653/cbd.c fptru_653/coding.c fptru_653/cpucycles.c fptru_653/fips202.c fptru_653/inverse.c fptru_653/kem.c fptru_653/pack.c fptru_653/pke.c fptru_653/poly.c fptru_653/randombytes.c fptru_653/reduce.c fptru_653/speed.c) #这里不能够有斜杠
    target_compile_options(fptru_653 PUBLIC -DFPTRU_N=653)
    target_include_directories(fptru_653 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_653)
    target_include_directories(fptru_653 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_653/poly_mul_n653q)
    set(_FPTRU_OBJS ${_FPTRU_OBJS} $<TARGET_OBJECTS:fptru_653>)
endif()

if(OQS_ENABLE_KEM_fptru_761)
    add_library(fptru_761 OBJECT kem_fptru_761.c fptru_761/poly_mul_n761q/radix_ntt_n761.c fptru_761/cbd.c fptru_761/coding.c fptru_761/cpucycles.c fptru_761/fips202.c fptru_761/inverse.c fptru_761/kem.c fptru_761/pack.c fptru_761/pke.c fptru_761/poly.c fptru_761/randombytes.c fptru_761/reduce.c fptru_761/speed.c) #这里不能够有斜杠
    target_compile_options(fptru_761 PUBLIC -DFPTRU_N=761)
    target_include_directories(fptru_761 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_761)
    target_include_directories(fptru_761 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_761/poly_mul_n761q)
    set(_FPTRU_OBJS ${_FPTRU_OBJS} $<TARGET_OBJECTS:fptru_761>)
endif()

if(OQS_ENABLE_KEM_fptru_1277)
    add_library(fptru_1277 OBJECT kem_fptru_1277.c fptru_1277/poly_mul_n1277q/radix_ntt_n1277.c fptru_1277/cbd.c fptru_1277/coding.c fptru_1277/cpucycles.c fptru_1277/fips202.c fptru_1277/inverse.c fptru_1277/kem.c fptru_1277/pack.c fptru_1277/pke.c fptru_1277/poly.c fptru_1277/randombytes.c fptru_1277/reduce.c fptru_1277/speed.c) #这里不能够有斜杠
    target_compile_options(fptru_1277 PUBLIC -DFPTRU_N=1277)
    target_include_directories(fptru_1277 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_1277)
    target_include_directories(fptru_1277 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_1277/poly_mul_n1277q)
    set(_FPTRU_OBJS ${_FPTRU_OBJS} $<TARGET_OBJECTS:fptru_1277>)
endif()

set(FPTRU_OBJS ${_FPTRU_OBJS} PARENT_SCOPE)
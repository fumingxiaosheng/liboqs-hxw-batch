set(_FPTRU_OBJS "")


if(OQS_ENABLE_KEM_fptru_761)
    add_library(fptru_761 OBJECT kem_fptru_761.c fptru_761/poly_mul_n761q/radix_ntt_n761.c fptru_761/cbd761.c fptru_761/coding761.c fptru_761/cpucycles761.c fptru_761/fips202761.c fptru_761/inverse761.c fptru_761/kem761.c fptru_761/pack761.c fptru_761/pke761.c fptru_761/poly761.c fptru_761/randombytes761.c fptru_761/reduce761.c fptru_761/speed761.c) #这里不能够有斜杠
    target_compile_options(fptru_761 PUBLIC -DFPTRU_N=761)
    target_include_directories(fptru_761 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_761)
    target_include_directories(fptru_761 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fptru_761/poly_mul_n761q)
    set(_FPTRU_OBJS ${_FPTRU_OBJS} $<TARGET_OBJECTS:fptru_761>)
endif()

set(FPTRU_OBJS ${_FPTRU_OBJS} PARENT_SCOPE)




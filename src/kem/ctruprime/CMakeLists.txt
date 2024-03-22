
set(_CTRUPRIME_OBJS "")

# TODO:这个应该和具体的密码方案实现有关

if(OQS_ENABLE_KEM_ctruprime_653)
    add_library(ctruprime_653_ref OBJECT kem_ctruprime_653.c ctruprime653/poly_mul_n653q/radix_ntt_n653.c ctruprime653/cbd.c ctruprime653/coding.c ctruprime653/cpucycles.c ctruprime653/fips202.c ctruprime653/inverse.c ctruprime653/kem.c ctruprime653/pack.c ctruprime653/pke.c ctruprime653/poly.c ctruprime653/randombytes.c ctruprime653/reduce.c ctruprime653/speed.c) #这里不能够有斜杠
    target_compile_options(ctruprime_653_ref PUBLIC -DFPTRU_N=653)
    target_include_directories(ctruprime_653_ref PRIVATE ${CMAKE_CURRENT_LIST_DIR}/ctruprime653)
    target_include_directories(ctruprime_653_ref PRIVATE ${CMAKE_CURRENT_LIST_DIR}/ctruprime653/poly_mul_n653q)
    # target_compile_options(kyber_512_ref PUBLIC -DKYBER_K=2) TODO:这里是否需要再设置一遍呢？
    set(_CTRUPRIME_OBJS ${_CTRUPRIME_OBJS} $<TARGET_OBJECTS:ctruprime_653_ref>)
endif()

set(CTRUPRIME_OBJS ${_CTRUPRIME_OBJS} PARENT_SCOPE)
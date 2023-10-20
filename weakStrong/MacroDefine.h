//
//  MacroDefine.h
//  weakStrong
//
//  Created by chenjingting on 2023/10/20.
//

#ifndef MacroDefine_h
#define MacroDefine_h

#define metamacro_concat(A, B) metamacro_concat_(A, B)
#define metamacro_concat_(A, B) A ## B

#define metamacro_argcount(...) metamacro_at(5, __VA_ARGS__, 5, 4, 3, 2, 1)

#define metamacro_at(N, ...) metamacro_concat(metamacro_at, N)(__VA_ARGS__)

#define metamacro_at0(...) metamacro_head(__VA_ARGS__)
#define metamacro_at1(_0, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at2(_0, _1, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at3(_0, _1, _2, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at4(_0, _1, _2, _3, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at5(_0, _1, _2, _3, _4, ...) metamacro_head(__VA_ARGS__)

#define metamacro_head(...) metamacro_head_(__VA_ARGS__, 0)
#define metamacro_head_(FIRST, ...) FIRST

#define metamacro_foreach_cxt0(MACRO, SEP, CONTEXT)
#define metamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)
#define metamacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) metamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) SEP MACRO(1, CONTEXT, _1)
#define metamacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) metamacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) SEP MACRO(2, CONTEXT, _2)

#define metamacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
metamacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
SEP \
MACRO(3, CONTEXT, _3)

#define metamacro_foreach_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
metamacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
SEP \
MACRO(4, CONTEXT, _4)

#define rac_weakify_(INDEX, CONTEXT, VAR) CONTEXT __typeof__(VAR) metamacro_concat(VAR, _weak_) = (VAR);


#define metamacro_foreach_cxt(MACRO, SEP, CONTEXT, ...) metamacro_concat(metamacro_foreach_cxt, metamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)

#define weakify(...) metamacro_foreach_cxt(rac_weakify_,, __weak, __VA_ARGS__)


// weakify(self)
// metamacro_concat(metamacro_foreach_cxt, metamacro_argcount(self))(rac_weakify_, , __weak,self)

// metamacro_argcount(self)
// metamacro_at(5, self, 5, 4, 3, 2, 1)
// metamacro_at5(self, 5, 4, 3, 2, 1)
// metamacro_head(1)
// metamacro_head_(1)
// 1

// metamacro_concat(metamacro_foreach_cxt, metamacro_argcount(self))
// metamacro_concat(metamacro_foreach_cxt, 1)
// metamacro_foreach_cxt1

// metamacro_foreach_cxt1(rac_weakify_, , __weak, self)
// rac_weakify_(0, __weak, self)

// __weak __typeof_(self) self_weak_ = (self);



// weakify(a, b)
// metamacro_foreach_cxt(rac_weakify_,, __weak, a, b)
// metamacro_concat(metamacro_foreach_cxt, metamacro_argcount(a, b))(rac_weakify_, , __weak, a, b)

// metamacro_argcount(a, b)
// metamacro_at(5, a, b, 5, 4, 3, 2, 1)
// metamacro_concat(metamacro_at, 5)(a, b, 5, 4, 3, 2, 1)
// metamacro_at5(a, b, 5, 4, 3, 2, 1)
// metamacro_head(2, 1)
// 2

// metamacro_concat(metamacro_foreach_cxt, 2)(rac_weakify_, , __weak, a, b)
// metamacro_foreach_cxt2(rac_weakify_, , __weak, a, b)
// metamacro_foreach_cxt1(rac_weakify_, , __weak, a) rac_weakify_(1, __weak, b)
// rac_weakify_(0, __weak, b) rac_weakify_(1, __weak, b)
// __weak __typeof_(a) a_weak_ = (a); __weak __typeof_(b) a_weak_ = (b);


#define strongify(...) \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wshadow\"") \
    metamacro_foreach(rac_strongify_,, __VA_ARGS__) \
    _Pragma("clang diagnostic pop")


#define metamacro_foreach(MACRO, SEP, ...) metamacro_foreach_cxt(metamacro_foreach_iter, SEP, MACRO, __VA_ARGS__)
#define metamacro_foreach_iter(INDEX, MACRO, ARG) MACRO(INDEX, ARG)

#define metamacro_foreach_cxt(MACRO, SEP, CONTEXT, ...) metamacro_concat(metamacro_foreach_cxt, metamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)
#define metamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)
#define metamacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) metamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) SEP MACRO(1, CONTEXT, _1)


#define rac_strongify_(INDEX, VAR) __strong __typeof__(VAR) VAR = metamacro_concat(VAR, _weak_);

// strongify(self)
// metamacro_foreach(rac_strongify_, , self)
// metamacro_foreach_cxt(metamacro_foreach_iter, , rac_strongify_, self)
// metamacro_concat(metamacro_foreach_cxt, metamacro_argcount(self))(metamacro_foreach_iter, , rac_strongify_, self)
// metamacro_foreach_cxt1(metamacro_foreach_iter, , rac_strongify_, self)
// metamacro_foreach_iter(0, rac_strongify_, self)
// rac_strongify_(0, self)
// __strong __typeof__(self) self = self_weak_;


// strongify(a, b)
// metamacro_foreach(rac_strongify_, , a, b)
// metamacro_foreach_cxt(metamacro_foreach_iter, , rac_strongify_, a, b)
// metamacro_concat(metamacro_foreach_cxt, 2)(metamacro_foreach_iter, , rac_strongify_, a, b)
// metamacro_foreach_cxt2(metamacro_foreach_iter, , rac_strongify_, a, b)
// metamacro_foreach_cxt1(metamacro_foreach_iter, , rac_strongify_, a) metamacro_foreach_iter(1, rac_strongify_, b)
// metamacro_foreach_iter(0, rac_strongify_, a) metamacro_foreach_iter(1, rac_strongify_, b)
// rac_strongify_(0, a) rac_strongify_(1, b)
// __strong __typeof__(a) a = a_weak_; __strong __typeof__(b) b = b_weak_;


#endif /* MacroDefine_h */

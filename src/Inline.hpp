


#ifndef Inline_HPP
#define Inline_HPP


#ifdef DEBUG
   #ifdef INLINE
      #undef INLINE
   #endif
   #define DONTINLINE __attribute__ ((noinline))
   #define INLINE DONTINLINE
#else
   #ifdef INLINE
      #undef INLINE
   #endif
   #define INLINE inline
   #define DONTINLINE
#endif


#endif // Inline_HPP


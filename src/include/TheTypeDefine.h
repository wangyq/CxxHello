/*
 * TheTypeDefine.h
 *
 *  Created on: 2016年4月16日
 *      Author: wang
 */

#ifndef SRC_INCLUDE_THETYPEDEFINE_H_
#define SRC_INCLUDE_THETYPEDEFINE_H_

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

typedef enum { FALSE=0, TRUE=1 } Boolean;

#ifdef S_OK
#undef S_OK
#endif

#ifdef S_FAILED
#undef S_FAILED
#endif
typedef enum { S_OK=0, S_FAILED=-1 } STATUS_CODE;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))



#endif /* SRC_INCLUDE_THETYPEDEFINE_H_ */

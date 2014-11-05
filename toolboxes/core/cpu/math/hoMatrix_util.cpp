
#include "hoMatrix_util.h"
#include "hoNDArray_elemwise.h"

#ifndef lapack_complex_float
    #define lapack_complex_float  std::complex<float> 
#endif // lapack_complex_float

#ifndef lapack_complex_double
    #define lapack_complex_double  std::complex<double> 
#endif // #ifndef lapack_complex_double

extern "C" void sgemm_(const char *transa, const char *transb, const lapack_int *m, const lapack_int *n, const lapack_int *k,
            const float *alpha, const float *a, const lapack_int *lda, const float *b, const lapack_int *ldb,
            const float *beta, float *c, const lapack_int *ldc);

extern "C" void dgemm_(const char *transa, const char *transb, const lapack_int *m, const lapack_int *n, const lapack_int *k,
            const double *alpha, const double *a, const lapack_int *lda, const double *b, const lapack_int *ldb,
            const double *beta, double *c, const lapack_int *ldc);

extern "C" void cgemm_(const char *transa, const char *transb, const lapack_int *m, const lapack_int *n, const lapack_int *k,
                    const lapack_complex_float *alpha, const lapack_complex_float *a, const lapack_int *lda,
                    const lapack_complex_float *b, const lapack_int *ldb, const lapack_complex_float *beta,
                    lapack_complex_float *c, const lapack_int *ldc);

extern "C" void zgemm_(const char *transa, const char *transb, const lapack_int *m, const lapack_int *n, const lapack_int *k,
            const lapack_complex_double *alpha, const lapack_complex_double *a, const lapack_int *lda,
            const lapack_complex_double *b, const lapack_int *ldb, const lapack_complex_double *beta,
            lapack_complex_double *c, const lapack_int *ldc);

extern "C" void ssyrk_( const char* uplo, const char *trans, const lapack_int *n, const lapack_int *k, const float *alpha, const float *a, const lapack_int *lda, const float *beta, float *c, const lapack_int *ldc);
extern "C" void dsyrk_( const char* uplo, const char *trans, const lapack_int *n, const lapack_int *k, const double *alpha, const double *a, const lapack_int *lda, const double *beta, double *c, const lapack_int *ldc);
extern "C" void csyrk_( const char* uplo, const char *trans, const lapack_int *n, const lapack_int *k, const lapack_complex_float *alpha, const lapack_complex_float *a, const lapack_int *lda, const lapack_complex_float *beta, lapack_complex_float *c, const lapack_int *ldc);
extern "C" void zsyrk_( const char* uplo, const char *trans, const lapack_int *n, const lapack_int *k, const lapack_complex_double *alpha, const lapack_complex_double *a, const lapack_int *lda, const lapack_complex_double *beta, lapack_complex_double *c, const lapack_int *ldc);

extern "C" void cherk_( const char* uplo, const char *trans, const lapack_int *n, const lapack_int *k, const lapack_complex_float *alpha, const lapack_complex_float *a, const lapack_int *lda, const lapack_complex_float *beta, lapack_complex_float *c, const lapack_int *ldc);
extern "C" void zherk_( const char* uplo, const char *trans, const lapack_int *n, const lapack_int *k, const lapack_complex_double *alpha, const lapack_complex_double *a, const lapack_int *lda, const lapack_complex_double *beta, lapack_complex_double *c, const lapack_int *ldc);

extern "C" void spotrf_( const char* uplo, const lapack_int* n, float* a, const lapack_int* lda, lapack_int* info );
extern "C" void dpotrf_( const char* uplo, const lapack_int* n, double* a, const lapack_int* lda, lapack_int* info );
extern "C" void cpotrf_( const char* uplo, const lapack_int* n, lapack_complex_float* a, const lapack_int* lda, lapack_int* info );
extern "C" void zpotrf_( const char* uplo, const lapack_int* n, lapack_complex_double* a, const lapack_int* lda, lapack_int* info );

extern "C" void ssyev_( const char* jobz, const char* uplo, const lapack_int* n, float* a,
        const lapack_int* lda, float* w, float* work, const lapack_int* lwork,
        lapack_int* info );

extern "C" void dsyev_( const char* jobz, const char* uplo, const lapack_int* n, double* a,
        const lapack_int* lda, double* w, double* work, const lapack_int* lwork,
        lapack_int* info );

extern "C" void cheev_( const char* jobz, const char* uplo, const lapack_int* n,
        lapack_complex_float* a, const lapack_int* lda, float* w, lapack_complex_float* work,
        const lapack_int* lwork, float* rwork, lapack_int* info );

extern "C" void zheev_( const char* jobz, const char* uplo, const lapack_int* n,
        lapack_complex_double* a, const lapack_int* lda, double* w,
        lapack_complex_double* work, const lapack_int* lwork, double* rwork,
        lapack_int* info );

extern "C" void spotrf_( const char* uplo, const lapack_int* n, float* a, const lapack_int* lda,
        lapack_int* info );

extern "C" void spotri_( const char* uplo, const lapack_int* n, float* a, const lapack_int* lda,
        lapack_int* info );

extern "C" void dpotrf_( const char* uplo, const lapack_int* n, double* a,
        const lapack_int* lda, lapack_int* info );

extern "C" void dpotri_( const char* uplo, const lapack_int* n, double* a,
        const lapack_int* lda, lapack_int* info );

extern "C" void cpotrf_( const char* uplo, const lapack_int* n, lapack_complex_float* a,
        const lapack_int* lda, lapack_int* info );

extern "C" void cpotri_( const char* uplo, const lapack_int* n, lapack_complex_float* a,
        const lapack_int* lda, lapack_int* info );

extern "C" void zpotrf_( const char* uplo, const lapack_int* n, lapack_complex_double* a,
        const lapack_int* lda, lapack_int* info );

extern "C" void zpotri_( const char* uplo, const lapack_int* n, lapack_complex_double* a,
        const lapack_int* lda, lapack_int* info );

extern "C" void strtri_( const char* uplo, const char* diag, const lapack_int* n, float* a,
        const lapack_int* lda, lapack_int* info );

extern "C" void dtrtri_( const char* uplo, const char* diag, const lapack_int* n, double* a,
        const lapack_int* lda, lapack_int* info );

extern "C" void ctrtri_( const char* uplo, const char* diag, const lapack_int* n,
        lapack_complex_float* a, const lapack_int* lda, lapack_int* info );

extern "C" void ztrtri_( const char* uplo, const char* diag, const lapack_int* n,
        lapack_complex_double* a, const lapack_int* lda, lapack_int* info );

extern "C" void sposv_( const char* uplo, const lapack_int* n, const lapack_int* nrhs, float* a,
        const lapack_int* lda, float* b, const lapack_int* ldb, lapack_int* info );

extern "C" void dposv_( const char* uplo, const lapack_int* n, const lapack_int* nrhs,
        double* a, const lapack_int* lda, double* b, const lapack_int* ldb,
        lapack_int* info );

extern "C" void cposv_( const char* uplo, const lapack_int* n, const lapack_int* nrhs,
        lapack_complex_float* a, const lapack_int* lda, lapack_complex_float* b,
        const lapack_int* ldb, lapack_int* info );

extern "C" void zposv_( const char* uplo, const lapack_int* n, const lapack_int* nrhs,
        lapack_complex_double* a, const lapack_int* lda, lapack_complex_double* b,
        const lapack_int* ldb, lapack_int* info );

extern "C" void sgetrf_( const lapack_int* m, const lapack_int* n, float* a, const lapack_int* lda,
        lapack_int* ipiv, lapack_int* info );

extern "C" void dgetrf_( const lapack_int* m, const lapack_int* n, double* a,
        const lapack_int* lda, lapack_int* ipiv, lapack_int* info );

extern "C" void cgetrf_( const lapack_int* m, const lapack_int* n, lapack_complex_float* a,
        const lapack_int* lda, lapack_int* ipiv, lapack_int* info );

extern "C" void zgetrf_( const lapack_int* m, const lapack_int* n, lapack_complex_double* a,
        const lapack_int* lda, lapack_int* ipiv, lapack_int* info );

extern "C" void sgetri_( const lapack_int* n, float* a, const lapack_int* lda,
        const lapack_int* ipiv, float* work, const lapack_int* lwork,
        lapack_int* info );

extern "C" void dgetri_( const lapack_int* n, double* a, const lapack_int* lda,
        const lapack_int* ipiv, double* work, const lapack_int* lwork,
        lapack_int* info );

extern "C" void cgetri_( const lapack_int* n, lapack_complex_float* a, const lapack_int* lda,
        const lapack_int* ipiv, lapack_complex_float* work, const lapack_int* lwork,
        lapack_int* info );

extern "C" void zgetri_( const lapack_int* n, lapack_complex_double* a, const lapack_int* lda,
        const lapack_int* ipiv, lapack_complex_double* work, const lapack_int* lwork,
        lapack_int* info );

namespace Gadgetron
{

// following matrix computation calls MKL functions
#if defined(USE_MKL) || defined(USE_LAPACK)

bool gemm(hoNDArray< std::complex<float> >& C, const hoNDArray< std::complex<float> >& A, const hoNDArray< std::complex<float> >& B)
{
    typedef std::complex<float> T;
    try
    {
        char TA, TB;

        GADGET_CHECK_RETURN_FALSE( (&C!=&A) && (&C!=&B) && (&A!=&B) );

        lapack_int lda = A.get_size(0);
        lapack_int ldb = B.get_size(0);
        const T* pA = A.begin(); 
        const T* pB = B.begin(); 

        lapack_int M = A.get_size(0);
        lapack_int K = A.get_size(1);

        lapack_int K2 = B.get_size(0);
        lapack_int N = B.get_size(1);

        GADGET_CHECK_RETURN_FALSE(K==K2);
        if ( (C.get_size(0)!=M) || (C.get_size(1)!=N) )
        {
            C.create(M, N);
        }

        T* pC = C.begin();
        lapack_int ldc = C.get_size(0);

         std::complex<float>  alpha(1), beta(0);

        TA = 'N';
        TB = 'N';

        cgemm_(&TA, &TB, &M, &N, &K, reinterpret_cast<lapack_complex_float*>(&alpha), reinterpret_cast<const lapack_complex_float*>(pA), &lda, reinterpret_cast<const lapack_complex_float*>(pB), &ldb, reinterpret_cast<lapack_complex_float*>(&beta), reinterpret_cast<lapack_complex_float*>(pC), &ldc);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in gemm(hoNDArray< std::complex<float> >& C, const hoNDArray< std::complex<float> >& A, const hoNDArray< std::complex<float> >& B) ...");
        return false;
    }
    return true;
}

template<> EXPORTCPUCOREMATH 
bool gemm(hoNDArray<float>& C, const hoNDArray<float>& A, bool transA, const hoNDArray<float>& B, bool transB)
{
    try
    {
        typedef float T;

        GADGET_CHECK_RETURN_FALSE( (&C!=&A) && (&C!=&B) && (&A!=&B) );

        char TA, TB;

        lapack_int lda = A.get_size(0);
        lapack_int ldb = B.get_size(0);
        const T* pA = A.begin(); 
        const T* pB = B.begin(); 

        lapack_int M = A.get_size(0);
        lapack_int K = A.get_size(1);
        if ( transA )
        { 
            M = A.get_size(1);
            K = A.get_size(0);
        }

        lapack_int K2 = B.get_size(0);
        lapack_int N = B.get_size(1);
        if ( transB )
        {
            K2 = B.get_size(1);
            N = B.get_size(0);
        }

        GADGET_CHECK_RETURN_FALSE(K==K2);
        if ( (C.get_size(0)!=M) || (C.get_size(1)!=N) )
        {
            C.create(M, N);
        }

        T* pC = C.begin();
        lapack_int ldc = C.get_size(0);

        float alpha(1), beta(0);

        if ( transA )
        {
            TA = 'T';
        }
        else
        {
            TA = 'N';
        }

        if ( transB )
        {
            TB = 'T';
        }
        else
        {
            TB = 'N';
        }

        sgemm_(&TA, &TB, &M, &N, &K, &alpha, reinterpret_cast<const float*>(pA), &lda, reinterpret_cast<const float*>(pB), &ldb, &beta, reinterpret_cast<float*>(pC), &ldc);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in gemm(hoNDArray<float>& C, const hoNDArray<float>& A, bool transA, const hoNDArray<float>& B, bool transB) ...");
        return false;
    }
    return true;
}

template<> EXPORTCPUCOREMATH 
bool gemm(hoNDArray<double>& C, const hoNDArray<double>& A, bool transA, const hoNDArray<double>& B, bool transB)
{
    try
    {
        typedef double T;

        GADGET_CHECK_RETURN_FALSE( (&C!=&A) && (&C!=&B) && (&A!=&B) );

        char TA, TB;

        lapack_int lda = A.get_size(0);
        lapack_int ldb = B.get_size(0);
        const T* pA = A.begin(); 
        const T* pB = B.begin(); 

        lapack_int M = A.get_size(0);
        lapack_int K = A.get_size(1);
        if ( transA )
        { 
            M = A.get_size(1);
            K = A.get_size(0);
        }

        lapack_int K2 = B.get_size(0);
        lapack_int N = B.get_size(1);
        if ( transB )
        {
            K2 = B.get_size(1);
            N = B.get_size(0);
        }

        GADGET_CHECK_RETURN_FALSE(K==K2);
        if ( (C.get_size(0)!=M) || (C.get_size(1)!=N) )
        {
            C.create(M, N);
        }

        T* pC = C.begin();
        lapack_int ldc = C.get_size(0);

        double alpha(1), beta(0);

        if ( transA )
        {
            TA = 'T';
        }
        else
        {
            TA = 'N';
        }

        if ( transB )
        {
            TB = 'T';
        }
        else
        {
            TB = 'N';
        }

        dgemm_(&TA, &TB, &M, &N, &K, &alpha, reinterpret_cast<const double*>(pA), &lda, reinterpret_cast<const double*>(pB), &ldb, &beta, reinterpret_cast<double*>(pC), &ldc);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in gemm(hoNDArray<double>& C, const hoNDArray<double>& A, bool transA, const hoNDArray<double>& B, bool transB) ...");
        return false;
    }
    return true;
}

template<> EXPORTCPUCOREMATH 
bool gemm(hoNDArray< std::complex<float> >& C, const hoNDArray< std::complex<float> >& A, bool transA, const hoNDArray< std::complex<float> >& B, bool transB)
{
    try
    {
        typedef  std::complex<float>  T;

        GADGET_CHECK_RETURN_FALSE( (&C!=&A) && (&C!=&B) && (&A!=&B) );

        char TA, TB;

        lapack_int lda = A.get_size(0);
        lapack_int ldb = B.get_size(0);
        const T* pA = A.begin(); 
        const T* pB = B.begin(); 

        lapack_int M = A.get_size(0);
        lapack_int K = A.get_size(1);
        if ( transA )
        { 
            M = A.get_size(1);
            K = A.get_size(0);
        }

        lapack_int K2 = B.get_size(0);
        lapack_int N = B.get_size(1);
        if ( transB )
        {
            K2 = B.get_size(1);
            N = B.get_size(0);
        }

        GADGET_CHECK_RETURN_FALSE(K==K2);
        if ( (C.get_size(0)!=M) || (C.get_size(1)!=N) )
        {
            C.create(M, N);
        }

        T* pC = C.begin();
        lapack_int ldc = C.get_size(0);

         std::complex<float>  alpha(1), beta(0);

        if ( transA )
        {
            TA = 'C';
        }
        else
        {
            TA = 'N';
        }

        if ( transB )
        {
            TB = 'C';
        }
        else
        {
            TB = 'N';
        }

        cgemm_(&TA, &TB, &M, &N, &K, reinterpret_cast<lapack_complex_float*>(&alpha), reinterpret_cast<const lapack_complex_float*>(pA), &lda, reinterpret_cast<const lapack_complex_float*>(pB), &ldb, reinterpret_cast<lapack_complex_float*>(&beta), reinterpret_cast<lapack_complex_float*>(pC), &ldc);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in gemm(hoNDArray< std::complex<float> >& C, const hoNDArray< std::complex<float> >& A, bool transA, const hoNDArray< std::complex<float> >& B, bool transB) ...");
        return false;
    }
    return true;
}

template<> EXPORTCPUCOREMATH 
bool gemm(hoNDArray< std::complex<double> >& C, const hoNDArray< std::complex<double> >& A, bool transA, const hoNDArray< std::complex<double> >& B, bool transB)
{
    try
    {
        typedef  std::complex<double>  T;

        GADGET_CHECK_RETURN_FALSE( (&C!=&A) && (&C!=&B) && (&A!=&B) );

        char TA, TB;

        lapack_int lda = A.get_size(0);
        lapack_int ldb = B.get_size(0);
        const T* pA = A.begin(); 
        const T* pB = B.begin(); 

        lapack_int M = A.get_size(0);
        lapack_int K = A.get_size(1);
        if ( transA )
        { 
            M = A.get_size(1);
            K = A.get_size(0);
        }

        lapack_int K2 = B.get_size(0);
        lapack_int N = B.get_size(1);
        if ( transB )
        {
            K2 = B.get_size(1);
            N = B.get_size(0);
        }

        GADGET_CHECK_RETURN_FALSE(K==K2);
        if ( (C.get_size(0)!=M) || (C.get_size(1)!=N) )
        {
            C.create(M, N);
        }

        T* pC = C.begin();
        lapack_int ldc = C.get_size(0);

         std::complex<double>  alpha(1), beta(0);

        if ( transA )
        {
            TA = 'C';
        }
        else
        {
            TA = 'N';
        }

        if ( transB )
        {
            TB = 'C';
        }
        else
        {
            TB = 'N';
        }

        zgemm_(&TA, &TB, &M, &N, &K, reinterpret_cast<lapack_complex_double*>(&alpha), reinterpret_cast<const lapack_complex_double*>(pA), &lda, reinterpret_cast<const lapack_complex_double*>(pB), &ldb, reinterpret_cast<lapack_complex_double*>(&beta), reinterpret_cast<lapack_complex_double*>(pC), &ldc);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in gemm(hoNDArray< std::complex<float> >& C, const hoNDArray< std::complex<float> >& A, bool transA, const hoNDArray< std::complex<float> >& B, bool transB) ...");
        return false;
    }
    return true;
}

/// ------------------------------------------------------------------------------------

template<> EXPORTCPUCOREMATH 
bool syrk(hoNDArray<float>& C, const hoNDArray<float>& A, char uplo, bool isATA)
{
    try
    {
        typedef float T;

        GADGET_CHECK_RETURN_FALSE( (&A!=&C) );

        char TA;

        lapack_int lda = (lapack_int)A.get_size(0);
        const T* pA = A.begin(); 

        lapack_int M = (lapack_int)A.get_size(0);
        lapack_int K = (lapack_int)A.get_size(1);
        if ( isATA )
        { 
            M = (lapack_int)A.get_size(1);
            K = (lapack_int)A.get_size(0);
        }

        if ( (C.get_size(0)!=M) || (C.get_size(1)!=M) )
        {
            C.create(M, M);
        }

        T* pC = C.begin();
        lapack_int ldc = (lapack_int)C.get_size(0);

        float alpha(1), beta(0);

        if ( isATA )
        {
            TA = 'T';
        }
        else
        {
            TA = 'N';
        }

        ssyrk_(&uplo, &TA, &M, &K, &alpha, pA, &lda, &beta, pC, &ldc);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in ssyrk(hoNDArray<float>& C, const hoNDArray<float>& A, char uplo, bool isATA) ...");
        return false;
    }
    return true;
}

template<> EXPORTCPUCOREMATH 
bool syrk(hoNDArray<double>& C, const hoNDArray<double>& A, char uplo, bool isATA)
{
    try
    {
        typedef double T;

        GADGET_CHECK_RETURN_FALSE( (&A!=&C) );

        char TA;

        lapack_int lda = (lapack_int)A.get_size(0);
        const T* pA = A.begin(); 

        lapack_int M = (lapack_int)A.get_size(0);
        lapack_int K = (lapack_int)A.get_size(1);
        if ( isATA )
        { 
            M = (lapack_int)A.get_size(1);
            K = (lapack_int)A.get_size(0);
        }

        if ( (C.get_size(0)!=M) || (C.get_size(1)!=M) )
        {
            C.create(M, M);
        }

        T* pC = C.begin();
        lapack_int ldc = (lapack_int)C.get_size(0);

        double alpha(1), beta(0);

        if ( isATA )
        {
            TA = 'T';
        }
        else
        {
            TA = 'N';
        }

        dsyrk_(&uplo, &TA, &M, &K, &alpha, pA, &lda, &beta, pC, &ldc);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in syrk(hoNDArray<double>& C, const hoNDArray<double>& A, char uplo, bool isATA) ...");
        return false;
    }
    return true;
}

template<> EXPORTCPUCOREMATH 
bool syrk(hoNDArray< std::complex<float> >& C, const hoNDArray< std::complex<float> >& A, char uplo, bool isATA)
{
    try
    {
        typedef  std::complex<float>  T;

        GADGET_CHECK_RETURN_FALSE( (&A!=&C) );

        char TA;

        lapack_int lda = (lapack_int)A.get_size(0);
        const T* pA = A.begin(); 

        lapack_int N = (lapack_int)A.get_size(0);
        lapack_int K = (lapack_int)A.get_size(1);
        if ( isATA )
        { 
            N = (lapack_int)A.get_size(1);
            K = (lapack_int)A.get_size(0);
        }

        GADGET_CHECK_RETURN_FALSE ( (C.get_size(0)==N) && (C.get_size(1)==N) );

        T* pC = C.begin();
        lapack_int ldc = (lapack_int)C.get_size(0);

        lapack_complex_float alpha(1), beta(0);

        if ( isATA )
        {
            TA = 'T';
        }
        else
        {
            TA = 'N';
        }

        csyrk_(&uplo, &TA, &N, &K, &alpha, pA, &lda, &beta, pC, &ldc);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in syrk(hoNDArray< std::complex<float> >& C, const hoNDArray< std::complex<float> >& A, char uplo, bool isATA) ...");
        return false;
    }
    return true;
}

template<> EXPORTCPUCOREMATH 
bool syrk(hoNDArray< std::complex<double> >& C, const hoNDArray< std::complex<double> >& A, char uplo, bool isATA)
{
    try
    {
        typedef  std::complex<double>  T;

        GADGET_CHECK_RETURN_FALSE( (&A!=&C) );

        char TA;

        lapack_int lda = (lapack_int)A.get_size(0);
        const T* pA = A.begin(); 

        lapack_int M = (lapack_int)A.get_size(0);
        lapack_int K = (lapack_int)A.get_size(1);
        if ( isATA )
        { 
            M = (lapack_int)A.get_size(1);
            K = (lapack_int)A.get_size(0);
        }

        if ( (C.get_size(0)!=M) || (C.get_size(1)!=M) )
        {
            C.create(M, M);
        }

        T* pC = C.begin();
        lapack_int ldc = (lapack_int)C.get_size(0);

        lapack_complex_double alpha(1), beta(0);

        if ( isATA )
        {
            TA = 'T';
        }
        else
        {
            TA = 'N';
        }

        zsyrk_(&uplo, &TA, &M, &K, &alpha, pA, &lda, &beta, pC, &ldc);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in syrk(hoNDArray< std::complex<double> >& C, const hoNDArray< std::complex<double> >& A, char uplo, bool isATA) ...");
        return false;
    }
    return true;
}

template<> EXPORTCPUCOREMATH 
bool herk(hoNDArray<float>& C, const hoNDArray<float>& A, char uplo, bool isAHA)
{
    return syrk(C, A, uplo, isAHA);
}

template<> EXPORTCPUCOREMATH 
bool herk(hoNDArray<double>& C, const hoNDArray<double>& A, char uplo, bool isAHA)
{
    return syrk(C, A, uplo, isAHA);
}

template<> EXPORTCPUCOREMATH 
bool herk(hoNDArray< std::complex<float> >& C, const hoNDArray< std::complex<float> >& A, char uplo, bool isAHA)
{
    try
    {
        typedef  std::complex<float>  T;

        GADGET_CHECK_RETURN_FALSE( (&A!=&C) );

        char TA;

        lapack_int lda = (lapack_int)A.get_size(0);
        const T* pA = A.begin(); 

        lapack_int N = (lapack_int)A.get_size(0);
        lapack_int K = (lapack_int)A.get_size(1);
        if ( isAHA )
        { 
            N = (lapack_int)A.get_size(1);
            K = (lapack_int)A.get_size(0);
        }

        if ( (C.get_size(0)!=N) || (C.get_size(1)!=N) )
        {
            C.create(N, N);
        }

        T* pC = C.begin();
        lapack_int ldc = (lapack_int)C.get_size(0);

        lapack_complex_float alpha(1), beta(0);

        if ( isAHA )
        {
            TA = 'C';
        }
        else
        {
            TA = 'N';
        }

        cherk_(&uplo, &TA, &N, &K, &alpha, pA, &lda, &beta, pC, &ldc);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in herk(hoNDArray< std::complex<float> >& C, const hoNDArray< std::complex<float> >& A, char uplo, bool isAHA) ...");
        return false;
    }
    return true;
}

template<> EXPORTCPUCOREMATH 
bool herk(hoNDArray< std::complex<double> >& C, const hoNDArray< std::complex<double> >& A, char uplo, bool isAHA)
{
    try
    {
        typedef  std::complex<double>  T;

        GADGET_CHECK_RETURN_FALSE( (&A!=&C) );

        char TA;

        lapack_int lda = (lapack_int)A.get_size(0);
        const T* pA = A.begin(); 

        lapack_int N = (lapack_int)A.get_size(0);
        lapack_int K = (lapack_int)A.get_size(1);
        if ( isAHA )
        { 
            N = (lapack_int)A.get_size(1);
            K = (lapack_int)A.get_size(0);
        }

        if ( (C.get_size(0)!=N) || (C.get_size(1)!=N) )
        {
            C.create(N, N);
        }

        T* pC = C.begin();
        lapack_int ldc = (lapack_int)C.get_size(0);

        lapack_complex_double alpha(1), beta(0);

        if ( isAHA )
        {
            TA = 'C';
        }
        else
        {
            TA = 'N';
        }

        zherk_(&uplo, &TA, &N, &K, &alpha, pA, &lda, &beta, pC, &ldc);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in herk(hoNDArray< std::complex<double> >& C, const hoNDArray< std::complex<double> >& A, char uplo, bool isAHA) ...");
        return false;
    }
    return true;
}

/// ------------------------------------------------------------------------------------

template<typename T> 
bool potrf(hoMatrix<T>& A, char uplo)
{
    try
    {
        if( A.get_number_of_elements()==0 ) return true;
        GADGET_CHECK_RETURN_FALSE(A.rows()==A.cols());

        lapack_int info;
        lapack_int n = (lapack_int)(A.rows());
        T* pA = A.begin();
        lapack_int lda = (lapack_int)(A.rows());

        if ( typeid(T)==typeid(float) )
        {
            spotrf_(&uplo, &n, reinterpret_cast<float*>(pA), &lda, &info);
        }
        else if ( typeid(T)==typeid(double) )
        {
            dpotrf_(&uplo, &n, reinterpret_cast<double*>(pA), &lda, &info);
        }
        else if ( typeid(T)==typeid( std::complex<float> ) )
        {
            cpotrf_(&uplo, &n, reinterpret_cast<lapack_complex_float*>(pA), &lda, &info);
        }
        else if ( typeid(T)==typeid( std::complex<double> ) )
        {
            zpotrf_(&uplo, &n, reinterpret_cast<lapack_complex_double*>(pA), &lda, &info);
        }
        else
        {
            GADGET_ERROR_MSG("potrf : unsupported type " << typeid(T).name());
            return false;
        }

        GADGET_CHECK_RETURN_FALSE(info==0);

        if ( uplo == 'U' )
        {
            GADGET_CHECK_RETURN_FALSE(A.lowerTri(0));
        }
        else
        {
            GADGET_CHECK_RETURN_FALSE(A.upperTri(0));
        }
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in potrf(hoMatrix<T>& A, char uplo) ...");
        return false;
    }
    return true;
}

template<typename T> 
bool heev(hoMatrix<T>& A, hoMatrix<typename realType<T>::Type>& eigenValue)
{
    try
    {
        lapack_int M = (lapack_int)A.rows();
        GADGET_CHECK_RETURN_FALSE(A.cols() == M);

        if ( (eigenValue.rows()!=M) || (eigenValue.cols()!=1) )
        {
            GADGET_CHECK_RETURN_FALSE(eigenValue.createMatrix(M, 1));
        }

        lapack_int info;
        char jobz = 'V';
        char uplo = 'L';
        T* pA = A.begin();
        typename realType<T>::Type* pEV = eigenValue.begin();

        //if ( typeid(T)==typeid(float) )
        //{
        //    info = LAPACKE_ssyev(LAPACK_COL_MAJOR, jobz, uplo, M, reinterpret_cast<float*>(pA), M, reinterpret_cast<float*>(pEV));
        //}
        //else if ( typeid(T)==typeid(double) )
        //{
        //    info = LAPACKE_dsyev(LAPACK_COL_MAJOR, jobz, uplo, M, reinterpret_cast<double*>(pA), M, reinterpret_cast<double*>(pEV));
        //}
        //else if ( typeid(T)==typeid( std::complex<float> ) )
        //{
        //    info = LAPACKE_cheev(LAPACK_COL_MAJOR, jobz, uplo, M, reinterpret_cast<lapack_complex_float*>(pA), M, reinterpret_cast<float*>(pEV));
        //}
        //else if ( typeid(T)==typeid( std::complex<double> ) )
        //{
        //    info = LAPACKE_zheev(LAPACK_COL_MAJOR, jobz, uplo, M, reinterpret_cast<lapack_complex_double*>(pA), M, reinterpret_cast<double*>(pEV));
        //}
        //else
        //{
        //    GADGET_ERROR_MSG("heev : unsupported type " << typeid(T).name());
        //    return false;
        //}

        lapack_int lwork;
        lwork = M*M;

        if ( typeid(T)==typeid(float) )
        {
            hoNDArray<float> work(M, M);
            ssyev_(&jobz, &uplo, &M, reinterpret_cast<float*>(pA), &M, reinterpret_cast<float*>(pEV), work.begin(), &lwork, &info);
        }
        else if ( typeid(T)==typeid(double) )
        {
            hoNDArray<double> work(M, M);
            dsyev_(&jobz, &uplo, &M, reinterpret_cast<double*>(pA), &M, reinterpret_cast<double*>(pEV), work.begin(), &lwork, &info);
        }
        else if ( typeid(T)==typeid( std::complex<float> ) )
        {
            hoNDArray< std::complex<float> > work(M, M);
            hoNDArray<float> rwork(3*M);
            cheev_(&jobz, &uplo, &M, reinterpret_cast<lapack_complex_float*>(pA), &M, reinterpret_cast<float*>(pEV), reinterpret_cast<lapack_complex_float*>(work.begin()), &lwork, rwork.begin(), &info);
        }
        else if ( typeid(T)==typeid( std::complex<double> ) )
        {
            hoNDArray< std::complex<double> > work(M, M);
            hoNDArray<double> rwork(3*M);
            zheev_(&jobz, &uplo, &M, reinterpret_cast<lapack_complex_double*>(pA), &M, reinterpret_cast<double*>(pEV), reinterpret_cast<lapack_complex_double*>(work.begin()), &lwork, rwork.begin(), &info);
        }
        else
        {
            GADGET_ERROR_MSG("heev : unsupported type " << typeid(T).name());
            return false;
        }

        GADGET_CHECK_RETURN_FALSE(info==0);
    }
    catch (...)
    {
        GADGET_ERROR_MSG("Errors in heev(hoMatrix<T>& A, hoMatrix<typename realType<T>::Type>& eigenValue) ... ");
        return false;
    }
    return true;
}

template<typename T> 
bool potri(hoMatrix<T>& A)
{
    try
    {
        if( A.get_number_of_elements()==0 ) return true;
        GADGET_CHECK_RETURN_FALSE(A.rows()==A.cols());

        lapack_int info;
        char uplo = 'L';
        lapack_int n = (lapack_int)A.rows();
        T* pA = A.begin();
        lapack_int lda = (lapack_int)A.rows();

        //if ( typeid(T)==typeid(float) )
        //{
        //    info = LAPACKE_spotrf(LAPACK_COL_MAJOR, uplo, n, reinterpret_cast<float*>(pA), lda);
        //    GADGET_CHECK_RETURN_FALSE(info==0);

        //    info = LAPACKE_spotri(LAPACK_COL_MAJOR, uplo, n, reinterpret_cast<float*>(pA), lda);
        //    GADGET_CHECK_RETURN_FALSE(info==0);
        //}
        //else if ( typeid(T)==typeid(double) )
        //{
        //    info = LAPACKE_dpotrf(LAPACK_COL_MAJOR, uplo, n, reinterpret_cast<double*>(pA), lda);
        //    GADGET_CHECK_RETURN_FALSE(info==0);

        //    info = LAPACKE_dpotri(LAPACK_COL_MAJOR, uplo, n, reinterpret_cast<double*>(pA), lda);
        //    GADGET_CHECK_RETURN_FALSE(info==0);
        //}
        //else if ( typeid(T)==typeid( std::complex<float> ) )
        //{
        //    info = LAPACKE_cpotrf(LAPACK_COL_MAJOR, uplo, n, reinterpret_cast<lapack_complex_float*>(pA), lda);
        //    GADGET_CHECK_RETURN_FALSE(info==0);

        //    info = LAPACKE_cpotri(LAPACK_COL_MAJOR, uplo, n, reinterpret_cast<lapack_complex_float*>(pA), lda);
        //    GADGET_CHECK_RETURN_FALSE(info==0);
        //}
        //else if ( typeid(T)==typeid( std::complex<double> ) )
        //{
        //    info = LAPACKE_zpotrf(LAPACK_COL_MAJOR, uplo, n, reinterpret_cast<lapack_complex_double*>(pA), lda);
        //    GADGET_CHECK_RETURN_FALSE(info==0);

        //    info = LAPACKE_zpotri(LAPACK_COL_MAJOR, uplo, n, reinterpret_cast<lapack_complex_double*>(pA), lda);
        //    GADGET_CHECK_RETURN_FALSE(info==0);
        //}
        //else
        //{
        //    GADGET_ERROR_MSG("potri : unsupported type " << typeid(T).name());
        //    return false;
        //}

        if ( typeid(T)==typeid(float) )
        {
            spotrf_(&uplo, &n, reinterpret_cast<float*>(pA), &lda, &info);
            GADGET_CHECK_RETURN_FALSE(info==0);

            spotri_(&uplo, &n, reinterpret_cast<float*>(pA), &lda, &info);
            GADGET_CHECK_RETURN_FALSE(info==0);
        }
        else if ( typeid(T)==typeid(double) )
        {
            dpotrf_(&uplo, &n, reinterpret_cast<double*>(pA), &lda, &info);
            GADGET_CHECK_RETURN_FALSE(info==0);

            dpotri_(&uplo, &n, reinterpret_cast<double*>(pA), &lda, &info);
            GADGET_CHECK_RETURN_FALSE(info==0);
        }
        else if ( typeid(T)==typeid( std::complex<float> ) )
        {
            cpotrf_(&uplo, &n, reinterpret_cast<lapack_complex_float*>(pA), &lda, &info);
            GADGET_CHECK_RETURN_FALSE(info==0);

            cpotri_(&uplo, &n, reinterpret_cast<lapack_complex_float*>(pA), &lda, &info);
            GADGET_CHECK_RETURN_FALSE(info==0);
        }
        else if ( typeid(T)==typeid( std::complex<double> ) )
        {
            zpotrf_(&uplo, &n, reinterpret_cast<lapack_complex_double*>(pA), &lda, &info);
            GADGET_CHECK_RETURN_FALSE(info==0);

            zpotri_(&uplo, &n, reinterpret_cast<lapack_complex_double*>(pA), &lda, &info);
            GADGET_CHECK_RETURN_FALSE(info==0);
        }
        else
        {
            GADGET_ERROR_MSG("potri : unsupported type " << typeid(T).name());
            return false;
        }
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in potri(hoMatrix<T>& A) ...");
        return false;
    }
    return true;
}

template<typename T> 
bool trtri(hoMatrix<T>& A, char uplo)
{
    try
    {
        if( A.get_number_of_elements()==0 ) return true;
        GADGET_CHECK_RETURN_FALSE(A.rows()==A.cols());

        lapack_int info;
        char diag = 'N';
        lapack_int n = (lapack_int)A.rows();
        T* pA = A.begin();
        lapack_int lda = (lapack_int)A.rows();

        /*if ( typeid(T)==typeid(float) )
        {
            info = LAPACKE_strtri(LAPACK_COL_MAJOR, uplo, diag, n, reinterpret_cast<float*>(pA), lda);
        }
        else if ( typeid(T)==typeid(double) )
        {
            info = LAPACKE_dtrtri(LAPACK_COL_MAJOR, uplo, diag, n, reinterpret_cast<double*>(pA), lda);
        }
        else if ( typeid(T)==typeid( std::complex<float> ) )
        {
            info = LAPACKE_ctrtri(LAPACK_COL_MAJOR, uplo, diag, n, reinterpret_cast<lapack_complex_float*>(pA), lda);
        }
        else if ( typeid(T)==typeid( std::complex<double> ) )
        {
            info = LAPACKE_ztrtri(LAPACK_COL_MAJOR, uplo, diag, n, reinterpret_cast<lapack_complex_double*>(pA), lda);
        }
        else
        {
            GADGET_ERROR_MSG("trtri : unsupported type " << typeid(T).name());
            return false;
        }*/

        if ( typeid(T)==typeid(float) )
        {
            strtri_(&uplo, &diag, &n, reinterpret_cast<float*>(pA), &lda, &info);
        }
        else if ( typeid(T)==typeid(double) )
        {
            dtrtri_(&uplo, &diag, &n, reinterpret_cast<double*>(pA), &lda, &info);
        }
        else if ( typeid(T)==typeid( std::complex<float> ) )
        {
            ctrtri_(&uplo, &diag, &n, reinterpret_cast<lapack_complex_float*>(pA), &lda, &info);
        }
        else if ( typeid(T)==typeid( std::complex<double> ) )
        {
            ztrtri_(&uplo, &diag, &n, reinterpret_cast<lapack_complex_double*>(pA), &lda, &info);
        }
        else
        {
            GADGET_ERROR_MSG("trtri : unsupported type " << typeid(T).name());
            return false;
        }

        GADGET_CHECK_RETURN_FALSE(info==0);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in trtri(hoMatrix<float>& A, char uplo) ...");
        return false;
    }
    return true;
}

template<typename T> 
bool posv(hoMatrix<T>& A, hoMatrix<T>& b)
{
    try
    {
        if( A.get_number_of_elements()==0 ) return true;
        if( b.get_number_of_elements()==0 ) return true;
        GADGET_CHECK_RETURN_FALSE(A.rows()==b.rows());

        lapack_int info;
        char uplo = 'L';
        lapack_int n = (lapack_int)A.rows();
        lapack_int nrhs = (lapack_int)b.cols();
        T* pA = A.begin();
        lapack_int lda = (lapack_int)A.rows();
        T* pB = b.begin();
        lapack_int ldb = (lapack_int)b.rows();

        /*if ( typeid(T)==typeid(float) )
        {
            info = LAPACKE_sposv(LAPACK_COL_MAJOR, uplo, n, nrhs, reinterpret_cast<float*>(pA), lda, reinterpret_cast<float*>(pB), ldb);
        }
        else if ( typeid(T)==typeid(double) )
        {
            info = LAPACKE_dposv(LAPACK_COL_MAJOR, uplo, n, nrhs, reinterpret_cast<double*>(pA), lda, reinterpret_cast<double*>(pB), ldb);
        }
        else if ( typeid(T)==typeid( std::complex<float> ) )
        {
            info = LAPACKE_cposv(LAPACK_COL_MAJOR, uplo, n, nrhs, reinterpret_cast<lapack_complex_float*>(pA), lda, reinterpret_cast<lapack_complex_float*>(pB), ldb);
        }
        else if ( typeid(T)==typeid( std::complex<double> ) )
        {
            info = LAPACKE_zposv(LAPACK_COL_MAJOR, uplo, n, nrhs, reinterpret_cast<lapack_complex_double*>(pA), lda, reinterpret_cast<lapack_complex_double*>(pB), ldb);
        }
        else
        {
            GADGET_ERROR_MSG("posv : unsupported type " << typeid(T).name());
            return false;
        }*/

        if ( typeid(T)==typeid(float) )
        {
            sposv_(&uplo, &n, &nrhs, reinterpret_cast<float*>(pA), &lda, reinterpret_cast<float*>(pB), &ldb, &info);
        }
        else if ( typeid(T)==typeid(double) )
        {
            dposv_(&uplo, &n, &nrhs, reinterpret_cast<double*>(pA), &lda, reinterpret_cast<double*>(pB), &ldb, &info);
        }
        else if ( typeid(T)==typeid( std::complex<float> ) )
        {
            cposv_(&uplo, &n, &nrhs, reinterpret_cast<lapack_complex_float*>(pA), &lda, reinterpret_cast<lapack_complex_float*>(pB), &ldb, &info);
        }
        else if ( typeid(T)==typeid( std::complex<double> ) )
        {
            zposv_(&uplo, &n, &nrhs, reinterpret_cast<lapack_complex_double*>(pA), &lda, reinterpret_cast<lapack_complex_double*>(pB), &ldb, &info);
        }
        else
        {
            GADGET_ERROR_MSG("posv : unsupported type " << typeid(T).name());
            return false;
        }

        GADGET_CHECK_RETURN_FALSE(info==0);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in posv(hoMatrix<T>& A, hoMatrix<T>& b) ...");
        return false;
    }
    return true;
}

/// Computes the LU factorization of a general m-by-n matrix
/// this function is called by general matrix inversion
template<typename T> 
bool getrf(hoMatrix<T>& A, hoNDArray<lapack_int>& ipiv)
{
    try
    {
        if( A.get_number_of_elements()==0 ) return true;

        lapack_int info;
        lapack_int m = (lapack_int)A.rows();
        lapack_int n = (lapack_int)A.cols();

        T* pA = A.begin();
        lapack_int lda = (lapack_int)A.rows();

        ipiv.create( GT_MIN(m, n) );
        lapack_int* pIPIV = ipiv.begin();

        //if ( typeid(T)==typeid(float) )
        //{
        //    info = LAPACKE_sgetrf(LAPACK_COL_MAJOR, m, n, reinterpret_cast<float*>(pA), lda, reinterpret_cast<lapack_int*>(pIPIV));
        //}
        //else if ( typeid(T)==typeid(double) )
        //{
        //    info = LAPACKE_dgetrf(LAPACK_COL_MAJOR, m, n, reinterpret_cast<double*>(pA), lda, reinterpret_cast<lapack_int*>(pIPIV));
        //}
        //else if ( typeid(T)==typeid( std::complex<float> ) )
        //{
        //    info = LAPACKE_cgetrf(LAPACK_COL_MAJOR, m, n, reinterpret_cast<lapack_complex_float*>(pA), lda, reinterpret_cast<lapack_int*>(pIPIV));
        //}
        //else if ( typeid(T)==typeid( std::complex<double> ) )
        //{
        //    info = LAPACKE_zgetrf(LAPACK_COL_MAJOR, m, n, reinterpret_cast<lapack_complex_double*>(pA), lda, reinterpret_cast<lapack_int*>(pIPIV));
        //}
        //else
        //{
        //    GADGET_ERROR_MSG("getrf : unsupported type " << typeid(T).name());
        //    return false;
        //}

        if ( typeid(T)==typeid(float) )
        {
            sgetrf_(&m, &n, reinterpret_cast<float*>(pA), &lda, reinterpret_cast<lapack_int*>(pIPIV), &info);
        }
        else if ( typeid(T)==typeid(double) )
        {
            dgetrf_(&m, &n, reinterpret_cast<double*>(pA), &lda, reinterpret_cast<lapack_int*>(pIPIV), &info);
        }
        else if ( typeid(T)==typeid( std::complex<float> ) )
        {
            cgetrf_(&m, &n, reinterpret_cast<lapack_complex_float*>(pA), &lda, reinterpret_cast<lapack_int*>(pIPIV), &info);
        }
        else if ( typeid(T)==typeid( std::complex<double> ) )
        {
            zgetrf_(&m, &n, reinterpret_cast<lapack_complex_double*>(pA), &lda, reinterpret_cast<lapack_int*>(pIPIV), &info);
        }
        else
        {
            GADGET_ERROR_MSG("getrf : unsupported type " << typeid(T).name());
            return false;
        }

        GADGET_CHECK_RETURN_FALSE(info==0);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in getrf(hoMatrix<T>& A, hoMatrix<T>& ipiv) ...");
        return false;
    }
    return true;
}

/// Computes the inverse of an LU-factored general matrix
template<typename T> 
bool getri(hoMatrix<T>& A)
{
    try
    {
        if( A.get_number_of_elements()==0 ) return true;

        lapack_int info;
        lapack_int m = (lapack_int)A.rows();
        lapack_int n = (lapack_int)A.cols();
        GADGET_CHECK_RETURN_FALSE(m==n);

        T* pA = A.begin();
        lapack_int lda = (lapack_int)A.rows();

        hoNDArray<lapack_int> ipiv;
        GADGET_CHECK_RETURN_FALSE(getrf(A, ipiv));

        lapack_int* pIPIV = ipiv.begin();

        lapack_int lwork = m*m;

        /*if ( typeid(T)==typeid(float) )
        {
            info = LAPACKE_sgetri(LAPACK_COL_MAJOR, m, reinterpret_cast<float*>(pA), lda, reinterpret_cast<lapack_int*>(pIPIV));
        }
        else if ( typeid(T)==typeid(double) )
        {
            info = LAPACKE_dgetri(LAPACK_COL_MAJOR, m, reinterpret_cast<double*>(pA), lda, reinterpret_cast<lapack_int*>(pIPIV));
        }
        else if ( typeid(T)==typeid( std::complex<float> ) )
        {
            info = LAPACKE_cgetri(LAPACK_COL_MAJOR, m, reinterpret_cast<lapack_complex_float*>(pA), lda, reinterpret_cast<lapack_int*>(pIPIV));
        }
        else if ( typeid(T)==typeid( std::complex<double> ) )
        {
            info = LAPACKE_zgetri(LAPACK_COL_MAJOR, m, reinterpret_cast<lapack_complex_double*>(pA), lda, reinterpret_cast<lapack_int*>(pIPIV));
        }
        else
        {
            GADGET_ERROR_MSG("getri : unsupported type " << typeid(T).name());
            return false;
        }*/

        if ( typeid(T)==typeid(float) )
        {
            hoNDArray<float> work(m, m);
            sgetri_(&m, reinterpret_cast<float*>(pA), &lda, reinterpret_cast<lapack_int*>(pIPIV), work.begin(), &lwork, &info);
        }
        else if ( typeid(T)==typeid(double) )
        {
            hoNDArray<double> work(m, m);
            dgetri_(&m, reinterpret_cast<double*>(pA), &lda, reinterpret_cast<lapack_int*>(pIPIV), work.begin(), &lwork, &info);
        }
        else if ( typeid(T)==typeid( std::complex<float> ) )
        {
            hoNDArray< std::complex<float> > work(m, m);
            cgetri_(&m, reinterpret_cast<lapack_complex_float*>(pA), &lda, reinterpret_cast<lapack_int*>(pIPIV), reinterpret_cast<lapack_complex_float*>(work.begin()), &lwork, &info);
        }
        else if ( typeid(T)==typeid( std::complex<double> ) )
        {
            hoNDArray< std::complex<double> > work(m, m);
            zgetri_(&m, reinterpret_cast<lapack_complex_double*>(pA), &lda, reinterpret_cast<lapack_int*>(pIPIV), reinterpret_cast<lapack_complex_double*>(work.begin()), &lwork, &info);
        }
        else
        {
            GADGET_ERROR_MSG("getri : unsupported type " << typeid(T).name());
            return false;
        }

        GADGET_CHECK_RETURN_FALSE(info==0);
    }
    catch(...)
    {
        GADGET_ERROR_MSG("Errors in getri(hoMatrix<T>& A) ...");
        return false;
    }
    return true;
}

// ---------------------------------------------

template EXPORTCPUCOREMATH bool potrf(hoMatrix<float>& A, char uplo);

template EXPORTCPUCOREMATH bool heev(hoMatrix<float>& A, hoMatrix<float>& eigenValue);

template EXPORTCPUCOREMATH bool potri(hoMatrix<float>& A);

template EXPORTCPUCOREMATH bool trtri(hoMatrix<float>& A, char uplo);

template EXPORTCPUCOREMATH bool posv(hoMatrix<float>& A, hoMatrix<float>& b);

template EXPORTCPUCOREMATH bool getrf(hoMatrix<float>& A, hoNDArray<lapack_int>& ipiv);

template EXPORTCPUCOREMATH bool getri(hoMatrix<float>& A);

// ---------------------------------------------

template EXPORTCPUCOREMATH bool potrf(hoMatrix<double>& A, char uplo);

template EXPORTCPUCOREMATH bool heev(hoMatrix<double>& A, hoMatrix<double>& eigenValue);

template EXPORTCPUCOREMATH bool potri(hoMatrix<double>& A);

template EXPORTCPUCOREMATH bool trtri(hoMatrix<double>& A, char uplo);

template EXPORTCPUCOREMATH bool posv(hoMatrix<double>& A, hoMatrix<double>& b);

template EXPORTCPUCOREMATH bool getrf(hoMatrix<double>& A, hoNDArray<lapack_int>& ipiv);

template EXPORTCPUCOREMATH bool getri(hoMatrix<double>& A);


// ---------------------------------------------

template EXPORTCPUCOREMATH bool potrf(hoMatrix< std::complex<float> >& A, char uplo);

template EXPORTCPUCOREMATH bool heev(hoMatrix< std::complex<float> >& A, hoMatrix<float>& eigenValue);

template EXPORTCPUCOREMATH bool potri(hoMatrix< std::complex<float> >& A);

template EXPORTCPUCOREMATH bool trtri(hoMatrix< std::complex<float> >& A, char uplo);

template EXPORTCPUCOREMATH bool posv(hoMatrix< std::complex<float> >& A, hoMatrix< std::complex<float> >& b);

template EXPORTCPUCOREMATH bool getrf(hoMatrix< std::complex<float> >& A, hoNDArray<lapack_int>& ipiv);

template EXPORTCPUCOREMATH bool getri(hoMatrix< std::complex<float> >& A);

// ---------------------------------------------

template EXPORTCPUCOREMATH bool potrf(hoMatrix< std::complex<double> >& A, char uplo);

template EXPORTCPUCOREMATH bool heev(hoMatrix< std::complex<double> >& A, hoMatrix<double>& eigenValue);

template EXPORTCPUCOREMATH bool potri(hoMatrix< std::complex<double> >& A);

template EXPORTCPUCOREMATH bool trtri(hoMatrix< std::complex<double> >& A, char uplo);

template EXPORTCPUCOREMATH bool posv(hoMatrix< std::complex<double> >& A, hoMatrix< std::complex<double> >& b);

template EXPORTCPUCOREMATH bool getrf(hoMatrix< std::complex<double> >& A, hoNDArray<lapack_int>& ipiv);

template EXPORTCPUCOREMATH bool getri(hoMatrix< std::complex<double> >& A);

#endif // defined(USE_MKL) || defined(USE_LAPACK)

#if defined(USE_MKL) || defined(USE_LAPACK)

    template<typename T> 
    bool heev(hoMatrix< std::complex<T> >& A, hoMatrix< std::complex<T> >& eigenValue)
    {
        try
        {
            long long M = (long long)A.rows();
            GADGET_CHECK_RETURN_FALSE(A.cols() == M);

            if ( (eigenValue.rows()!=M) || (eigenValue.cols()!=1) )
            {
                GADGET_CHECK_RETURN_FALSE(eigenValue.createMatrix(M, 1));
            }

            hoMatrix<typename realType<T>::Type> D(M, 1);
            GADGET_CHECK_RETURN_FALSE(heev(A, D));
            eigenValue.copyFrom(D);
        }
        catch (...)
        {
            GADGET_ERROR_MSG("Errors in heev(hoMatrix< std::complex<T> >& A, hoMatrix< std::complex<T> >& eigenValue) ... ");
            return false;
        }
        return true;
    }

    template<typename T> 
    bool SolveLinearSystem_Tikhonov(hoMatrix<T>& A, hoMatrix<T>& b, hoMatrix<T>& x, double lamda)
    {
        GADGET_CHECK_RETURN_FALSE(b.rows()==A.rows());

        hoMatrix<T> AHA(A.cols(), A.cols());
        Gadgetron::clear(AHA);

        // hoMatrix<T> ACopy(A);
        // GADGET_CHECK_RETURN_FALSE(gemm(AHA, ACopy, true, A, false));

        char uplo = 'L';
        bool isAHA = true;
        GADGET_CHECK_RETURN_FALSE(herk(AHA, A, uplo, isAHA));

        GADGET_CHECK_RETURN_FALSE(x.createMatrix(A.cols(), b.cols()));
        GADGET_CHECK_RETURN_FALSE(gemm(x, A, true, b, false));

        // apply the Tikhonov regularization
        // Ideally, we shall apply the regularization is lamda*maxEigenValue
        // However, computing the maximal eigenvalue is computational intensive
        // A natural alternative is to use the trace of AHA matrix, which is the sum of all eigen values
        // Since all eigen values are positive, the lamda*maxEigenValue is only ~10-20% different from lamda*sum(all eigenValues)
        // for more information, refer to:
        // Tikhonov A.N., Goncharsky A.V., Stepanov V.V., Yagola A.G., 1995, 
        // Numerical Methods for the Solution of Ill-Posed Problems, Kluwer Academic Publishers.

        size_t col = AHA.cols();
        size_t c;

        double trA = std::abs(AHA(0, 0));
        for ( c=1; c<col; c++ )
        {
            trA += std::abs(AHA(c, c));
        }

        double value = trA*lamda/col;
        for ( c=0; c<col; c++ )
        {
            AHA(c,c) = T( (typename realType<T>::Type)(std::abs(AHA(c, c)) + value) );
        }

        GADGET_CHECK_RETURN_FALSE(posv(AHA, x));

        return true;
    }

    template EXPORTCPUCOREMATH bool heev(hoMatrix< std::complex<float> >& A, hoMatrix< std::complex<float> >& eigenValue);
    template EXPORTCPUCOREMATH bool heev(hoMatrix< std::complex<double> >& A, hoMatrix< std::complex<double> >& eigenValue);

    template EXPORTCPUCOREMATH bool SolveLinearSystem_Tikhonov(hoMatrix<float>& A, hoMatrix<float>& b, hoMatrix<float>& x, double lamda);
    template EXPORTCPUCOREMATH bool SolveLinearSystem_Tikhonov(hoMatrix<double>& A, hoMatrix<double>& b, hoMatrix<double>& x, double lamda);
    template EXPORTCPUCOREMATH bool SolveLinearSystem_Tikhonov(hoMatrix< std::complex<float> >& A, hoMatrix< std::complex<float> >& b, hoMatrix< std::complex<float> >& x, double lamda);
    template EXPORTCPUCOREMATH bool SolveLinearSystem_Tikhonov(hoMatrix< std::complex<double> >& A, hoMatrix< std::complex<double> >& b, hoMatrix< std::complex<double> >& x, double lamda);

#endif // defined(USE_MKL) || defined(USE_LAPACK)

}
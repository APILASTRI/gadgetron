/*
* linalg_test.cpp
*
*  Created on: Dec 9, 2011
*      Author: Michael S. Hansen
*/

#include <iostream>
#include <hoNDArray.h>
#include <hoNDArray_fileio.h>
#include <hoNDArray_utils.h>
#include <matrix_vector_op.h>
#include <matrix_decomposition.h>
#include "GadgetronTimer.h"
#include "hoNDArray_math_util.h"
#include "hoNDArray_elemwise.h"
#include "hoMatrix_util.h"
#include "hoNDMath_util.h"
#include "hoNDFFT.h"
#include <fftw3.h>
#include <valarray>
#include <omp.h>

#define DIFF_LIMIT 1e-5

using namespace Gadgetron;

double mcompare(hoNDArray< std::complex<float> >* A, hoNDArray< std::complex<float> >* B)
{
    float comp = 0.0;
    float root_sum = 0.0;
    if (A->get_number_of_elements() != B->get_number_of_elements()) {
        GDEBUG_STREAM("Wrong number of elements in comparison" << std::endl);
        return 9e30;
    }

    hoNDArray< std::complex<float> > diff;
    Gadgetron::subtract(*A, *B, diff);

    /*std::complex<float>* a = A->get_data_ptr();
    std::complex<float>* b = B->get_data_ptr();
    for (unsigned long int i = 0; i < A->get_number_of_elements(); i++) {
    comp += abs(a[i]-b[i]);
    root_sum += abs(a[i]*conj(b[i]));
    }
    comp /= root_sum;*/

    Gadgetron::norm1(diff, comp);

    std::complex<float> r;
    Gadgetron::dotc(*A, *B, r);
    if ( std::abs(r) > 0 ) comp /= std::abs(r);
    return comp;
}

double mcompare(hoNDArray< float >* A, hoNDArray< float >* B)
{
    float comp = 0.0;
    float root_sum = 0.0;
    if (A->get_number_of_elements() != B->get_number_of_elements()) {
        GDEBUG_STREAM("Wrong number of elements in comparison" << std::endl);
        return 9e30;
    }

    hoNDArray< float > diff;
    Gadgetron::subtract(*A, *B, diff);

    /*std::complex<float>* a = A->get_data_ptr();
    std::complex<float>* b = B->get_data_ptr();
    for (unsigned long int i = 0; i < A->get_number_of_elements(); i++) {
    comp += abs(a[i]-b[i]);
    root_sum += abs(a[i]*conj(b[i]));
    }
    comp /= root_sum;*/

    Gadgetron::norm1(diff, comp);

    float r;
    Gadgetron::math::dotu(A->get_number_of_elements(), A->begin(), B->begin(), r);
    if ( std::abs(r) > 0 )  comp /= std::abs(r);
    return comp;
}

void compare_result(hoNDArray< std::complex<float> >& res, hoNDArray< std::complex<float> >& res_math, const std::string& msg)
{
    double diff = mcompare(&res, &res_math);
    if (diff > DIFF_LIMIT)
    {
        GDEBUG_STREAM(msg << " - FAILED with diff: " << diff << std::endl);
    }
    else
    {
        GDEBUG_STREAM(msg << " - SUCCESS with diff: " << diff << std::endl);
    }
}

void compare_result(hoNDArray< float >& res, hoNDArray< float >& res_math, const std::string& msg)
{
    double diff = mcompare(&res, &res_math);
    if (diff > DIFF_LIMIT)
    {
        GDEBUG_STREAM(msg << " - FAILED with diff: " << diff << std::endl);
    }
    else
    {
        GDEBUG_STREAM(msg << " - SUCCESS with diff: " << diff << std::endl);
    }
}

/*
*   Simple test program for linear algebra routines.
*/
int main(int argc, char** argv)
{
    GDEBUG_STREAM("Simple test of linear algebra routines" << std::endl);
    if (argc != 2) {
        GDEBUG_STREAM("Usage: linalg_test <folder_with_test_data>" << std::endl);
        return -1;
    }

    std::string filenameA = std::string(argv[1]) + std::string("/A.cplx");
    std::string filenameB = std::string(argv[1]) + std::string("/B.cplx");
    std::string filenameC1 = std::string(argv[1]) + std::string("/C1.cplx");
    std::string filenameC2 = std::string(argv[1]) + std::string("/C2.cplx");
    std::string filenameS = std::string(argv[1]) + std::string("/S.cplx");
    std::string filenameS_chol = std::string(argv[1]) + std::string("/S_chol.cplx");
    std::string filenameS_chol_inv = std::string(argv[1]) + std::string("/S_chol_inv.cplx");

    boost::shared_ptr< hoNDArray<std::complex<float> > > A = read_nd_array< std::complex<float> >(filenameA.c_str());
    boost::shared_ptr< hoNDArray<std::complex<float> > > B = read_nd_array< std::complex<float> >(filenameB.c_str());
    boost::shared_ptr< hoNDArray<std::complex<float> > > C1 = read_nd_array< std::complex<float> >(filenameC1.c_str());
    boost::shared_ptr< hoNDArray<std::complex<float> > > C2 = read_nd_array< std::complex<float> >(filenameC2.c_str());

    boost::shared_ptr< hoNDArray<std::complex<float> > > S = read_nd_array< std::complex<float> >(filenameS.c_str());
    boost::shared_ptr< hoNDArray<std::complex<float> > > S_chol = read_nd_array< std::complex<float> >(filenameS_chol.c_str());
    boost::shared_ptr< hoNDArray<std::complex<float> > > S_chol_inv = read_nd_array< std::complex<float> >(filenameS_chol_inv.c_str());

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("matrix multiplication");
    GDEBUG_STREAM("------------------------------------------------------------------");

    std::complex<float> alpha(1.0,0);
    std::complex<float> beta(1.0,0);
    double diff;

    /*{
    GadgetronTimer t("GEMM Time (system)", true);
    hoNDArray_gemm( A.get(), B.get(), alpha,  C1.get(), beta);
    GDEBUG_STREAM(C1->get_size(0) << ", " << C1->get_size(1) << ", " << C1->get_number_of_elements() << std::endl);
    }

    {
    GadgetronTimer t("GEMM Time (MKL)", true);
    gemm( *C1.get(), *B.get(), *A.get());
    GDEBUG_STREAM(C1->get_size(0) << ", " << C1->get_size(1) << ", " << C1->get_number_of_elements() << std::endl);
    }

    {
    GadgetronTimer t("Write time", true);
    write_nd_array< std::complex<float> >(C1.get(), "C2_calc.cplx");
    }

    double diff;
    {
    GadgetronTimer compare("CompareTime", true);
    diff = mcompare(C1.get(),C2.get());
    }

    if (diff > DIFF_LIMIT) {
    GDEBUG_STREAM("Complex GEMM FAILED with diff: " << diff << std::endl);
    return -1;
    } else {
    GDEBUG_STREAM("Complex GEMM SUCCESS with diff: " << diff << std::endl);
    }

    hoNDArray_choldc(S.get());
    zero_tril(S.get());

    write_nd_array< std::complex<float> >(S.get(), "S_chol_calc.cplx");

    diff = mcompare(S.get(),S_chol.get());
    if (diff > DIFF_LIMIT) {
    GDEBUG_STREAM("Complex Cholesky decomposition FAILED with diff: " << diff << std::endl);
    return -1;
    } else {
    GDEBUG_STREAM("Complex Cholesky decomposition SUCCESS with diff: " << diff << std::endl);
    }

    hoNDArray_inv_lower_triangular(S.get());

    write_nd_array< std::complex<float> >(S.get(), "S_chol_inv_calc.cplx");

    diff = mcompare(S.get(),S_chol_inv.get());
    if (diff > DIFF_LIMIT) {
    GDEBUG_STREAM("Complex Triangular inversion FAILED with diff: " << diff << std::endl);
    return -1;
    } else {
    GDEBUG_STREAM("Complex Triangular inversion SUCCESS with diff: " << diff << std::endl);
    }*/

    hoNDArray<std::complex<float> > a(*A);
    hoNDArray<std::complex<float> > b(*A);

    Gadgetron::scal( std::complex<float>(2), b);

    float r;

    hoNDArray<std::complex<float> > res, res_math;
    hoNDArray<float > res_f, res_f_math;

    {
        GadgetronTimer t("allocate res", true);
        res = a;
        res_math = a;

        res_f.create(a.get_dimensions());
        res_f_math.create(a.get_dimensions());
    }

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("axpy");
    GDEBUG_STREAM("------------------------------------------------------------------");

    {
        GadgetronTimer t("axpy Time (MKL)", true);
        Gadgetron::axpy( alpha, a, b, res);
    }

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector add");
    GDEBUG_STREAM("------------------------------------------------------------------");

    {
        GadgetronTimer t("vzAdd Time (MKL)", true);
        Gadgetron::add( *A.get(), *A.get(), res);
    }

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector subtract");
    GDEBUG_STREAM("------------------------------------------------------------------");

    {
        GadgetronTimer t("vzSub Time (MKL)", true);
        Gadgetron::subtract( a, b, res);
    }


    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector multiplication");
    GDEBUG_STREAM("------------------------------------------------------------------");

    {
        GadgetronTimer t("vzMul Time (MKL)", true);
        Gadgetron::multiply( a, b, res);
    }

    compare_result(res, res_math, "multiply");

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector addEpsilon");
    GDEBUG_STREAM("------------------------------------------------------------------");

    res = a;
    res_math = a;

    {
        GadgetronTimer t("addEpsilon Time (MKL)", true);
        Gadgetron::addEpsilon( res );
    }

    compare_result(res, res_math, "addEpsilon");

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector divide");
    GDEBUG_STREAM("------------------------------------------------------------------");

    {
        GadgetronTimer t("divide Time (MKL)", true);
        Gadgetron::divide( a, res, res);
    }

    compare_result(res, res_math, "divide");

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector sqrt");
    GDEBUG_STREAM("------------------------------------------------------------------");

    {
        GadgetronTimer t("sqrt Time (MKL)", true);
        Gadgetron::sqrt( a, res);
    }

    compare_result(res, res_math, "sqrt");

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector conjugate");
    GDEBUG_STREAM("------------------------------------------------------------------");

    {
        GadgetronTimer t("conjugate Time (MKL)", true);
        Gadgetron::conjugate( a, res);
    }

    compare_result(res, res_math, "conjugate");

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector conjugate multiplication");
    GDEBUG_STREAM("------------------------------------------------------------------");

    {
        GadgetronTimer t("vcMulByConj Time (MKL)", true);
        Gadgetron::multiplyConj( a, b, res);
    }

    compare_result(res, res_math, "multiplyConj");

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector scal");
    GDEBUG_STREAM("------------------------------------------------------------------");

    res = a;
    res_math = a;

    {
        GadgetronTimer t("scal Time (MKL)", true);
        Gadgetron::scal( alpha, a);
    }

    compare_result(res, res_math, "scal");

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector dotc");
    GDEBUG_STREAM("------------------------------------------------------------------");

    std::complex<float> rdotc(0);

    {
        GadgetronTimer t("dotc Time (MKL)", true);
        rdotc = Gadgetron::dotc( a, b);
    }
    GDEBUG_STREAM("dotc = " << rdotc << std::endl);

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector dotu");
    GDEBUG_STREAM("------------------------------------------------------------------");

    std::complex<float> rdotu;

    {
        GadgetronTimer t("dotu Time (MKL)", true);
        rdotu = Gadgetron::dotu( a, b );
    }
    GDEBUG_STREAM("dotu = " << rdotu << std::endl);

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector absolute");
    GDEBUG_STREAM("------------------------------------------------------------------");

    {
        GadgetronTimer t("absolute Time (MKL)", true);
        Gadgetron::absolute( a, res);
    }

    compare_result(res, res_math, "absolute");

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector argument");
    GDEBUG_STREAM("------------------------------------------------------------------");

    {
        GadgetronTimer t("argument Time (MKL)", true);
        Gadgetron::argument( a, res_f);
    }

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("vector inv");
    GDEBUG_STREAM("------------------------------------------------------------------");

    {
        GadgetronTimer t("inv Time (MKL)", true);
        Gadgetron::inv( a, res);
    }

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("norm2");
    GDEBUG_STREAM("------------------------------------------------------------------");

    float rn;

    {
        GadgetronTimer t("Time (MKL)", true);
        Gadgetron::norm2( a, rn);
    }
    GDEBUG_STREAM("nrm2 = " << rn << std::endl);

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("norm1");
    GDEBUG_STREAM("------------------------------------------------------------------");

    {
        GadgetronTimer t("Time (MKL)", true);
        Gadgetron::norm1( a, rn);
    }
    GDEBUG_STREAM("nrm1 = " << rn << std::endl);

    GDEBUG_STREAM("------------------------------------------------------------------");
    GDEBUG_STREAM("conv2");
    GDEBUG_STREAM("------------------------------------------------------------------");

    hoNDArray<std::complex<float> > ker;
    ker.create(3, 3);
    Gadgetron::fill(ker, std::complex<float>(1) );

    {
        GadgetronTimer t("conv2 Time (MKL)", true);
        Gadgetron::conv2( a, ker, res);
    }
}

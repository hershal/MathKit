/* MathKit MKMatirx Testing */

#include <sstream>
#include <iostream>
#include <random>
#include <ctime>

#include "MKMatrix.hpp"
#include "TKCumulableAttribute.hpp"

auto fill_test(std::size_t vector_len)
    -> std::shared_ptr<TKCumulableAttribute<std::size_t> >;

int main () {
    std::cout << "declaration" << std::endl;
    MKMatrix<float> mat;
    std::cout << "instantiation" << std::endl;
    mat = MKMatrix<float>(4);
    std::cout << "RSET: " << mat.size() << std::endl;

    /* mat[0] = 1; */
    mat[0][0] = 1;  mat[0][1] = 2;  mat[0][2] = 1;
    mat[1][0] = 3;  mat[1][1] = 10; mat[1][2] = 6;
    mat[2][0] = 0;  mat[2][1] = 8;  mat[2][2] = 14;
    mat[3] = 10;
    std::cout << "MAT PRINTOUT: " <<  mat.to_string() << std::endl;
}

/* int main_test () { */
/*     std::size_t len = 100; */
/*     std::size_t vector_len = (float)(pow(10000.0, 0.5)); */
/*  */
/*     std::size_t insertion_num_insertions = (float)(pow(100000.0, 0.5)); */
/*     float insertion_percentage_out_of_bounds = 0.25; */
/*  */
/*     /\* Fill Test *\/ */
/*     auto fill_test_results = TKCumulableAttribute<std::size_t>(); */
/*     for (auto i=0; i<len; ++i) { */
/*         fill_test_results += *(fill_test(vector_len)); */
/*     } */
/*     std::cout << "fill test\n" << */
/*         fill_test_results.to_string() << "\n" << std::endl; */
/*  */
/* } */
/*  */
/* auto fill_test(std::size_t vector_len) */
/*     -> std::shared_ptr<TKCumulableAttribute<std::size_t> > { */
/*  */
/*     std::srand(std::time(0)); */
/*     std::size_t num_total = 0; */
/*  */
/*     /\* Create the vectors *\/ */
/*     MKVector < MKVector<float> > v1(vector_len, MKVector<float>(vector_len)); */
/*     MKVector < MKVector<float> > v2(vector_len, MKVector<float>(vector_len)); */
/*     std::vector<float> fill_value(vector_len); */
/*  */
/*     /\* Populate the vector values *\/ */
/*     for (auto i=0; i<vector_len; ++i) { */
/*         fill_value[i] = (float)(rand()); */
/*         v1[i] = fill_value[i]; */
/*         for (auto j=0; j<vector_len; ++j) { */
/*             v2[i][j] = fill_value[i]; */
/*             ++num_total; */
/*         } */
/*     } */
/*  */
/*     /\* Verify output *\/ */
/*     for (auto i=0; i<vector_len; ++i) { */
/*         for (auto j=0; j<vector_len; ++j) { */
/*             BOOST_ASSERT_MSG(((v1[i][j] == v2[i][j]) && */
/*                               (v1[i][j] == fill_value[i])), */
/*                              (std::stringstream() */
/*                               << fill_value[i] << "!=" */
/*                               << v1[i][j]<< "!=" */
/*                               << v2[i][j]) */
/*                              .str().c_str()); */
/*         } */
/*     } */
/*  */
/*     /\* Generate result receipt *\/ */
/*     auto m = std::make_shared<TKCumulableAttribute<std::size_t> >(); */
/*     (*m)[k_num_total] = num_total; */
/*     return m; */
/* } */

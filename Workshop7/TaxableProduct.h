#ifndef W7_TAXABLEPRODUCT_H_
#define W7_TAXABLEPRODUCT_H_

#include "Product.h"
/*
namespace w7 {

  class TaxableProduct : public Product {
    enum TAX { HST, PST, TAX_TOTAL };
    size_t taxStatusArray[TAX_TOTAL];
    std::string taxstatus;
  public: 
    TaxableProduct(): taxstatus("") {
      taxStatusArray[HST] = 13; // 13 %
      taxStatusArray[PST] = 8;  // 8 %
    }

    // Receives a reference to the input file stream, 
    // reads the next record from the stream, allocates 
    // memory for the corresponding iProduct object
    iProduct* readProduct(std::ifstream& ins)
    {
      Product::readProduct(ins);
      // Find tax status (HST, PST)
      std::getline(ins, this->taxstatus);

      return this;
    }
  };
}
*/
#endif

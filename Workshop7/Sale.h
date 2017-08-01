// OOP345 Workshop 7: STL Containers
// File Sale.h
// Version 1.0
// Date 2017-07-14
// Author Jongkuk Lee ( jlee465@myseneca.ca, 127730158 )
// Description
//  contains the list of products sold to the customer
//
// Revision History
///////////////////////////////////////////////////////////
// Name     Date    Reason
//
///////////////////////////////////////////////////////////
#ifndef W7_SALE_H_
#define W7_SALE_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include "iProduct.h"
#define VERBOSE 0 

namespace w7 {

  class Sale {
    std::vector<iProduct*> salesProducts;
  public:
    // Constructor
    Sale(const char* filename)
    {
      std::ifstream ins(filename, std::ios::out);

      if (!ins.is_open())
        std::cerr << filename << " cannot be open!" << std::endl;
      else
      {
        if (VERBOSE) std::cout << filename << " is open!" << std::endl;
        while (!ins.eof())
          salesProducts.push_back(readProduct(ins));
      }
    }

    // Destructor
    ~Sale()
    {
      // Deallocate memory
      for (auto e : salesProducts)
        delete e;
    }

    // Displays the sale information with column headings 
    // and the total sale amount including taxes paid
    // The product number and cost occupy fields of width 10
    void display(std::ostream& os) const
    {
      double totalCost = 0.0f;
      os << "Product No      Cost Taxable\n";
      for (auto e : salesProducts)
      {
        std::cout << *e << std::endl;
        totalCost += e->getCharge();
      }
      os << "     Total    " << totalCost << "\n";
    }
  };
}
#endif

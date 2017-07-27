#ifndef W7_I_PRODUCT_H_
#define W7_I_PRODUCT_H_

// Workshop 7 - STL Containers
// iProduct.h

#include <iostream>
#include <fstream>
#include <iomanip>
#define VERBOSE 0

namespace w7 {

  class iProduct {
  public:
    virtual double getCharge() const = 0;
    virtual void display(std::ostream&) const = 0;
  };

  class Product : public iProduct {
    size_t number;
    double cost;
  public:
    Product(size_t num, double cost): number(num), cost(cost) {}
    virtual double getCharge() const
    {
      return this->cost;
    }
    virtual void display(std::ostream& os) const
    {
      os.setf(std::ios::fixed);
      os.precision(2);
      os << std::setw(10) << this->number << std::setw(10) << this->cost;
    }
    virtual void setNumber(size_t num)
    {
      this->number = num;
    }
    virtual void setCost(double cost)
    {
      this->cost = cost;
    }
  };

  class TaxableProduct : public Product {
    enum TAX { HST, PST, TAX_TOTAL };
    double taxStatusArray[TAX_TOTAL];
    std::string taxstatus;
  public:
    TaxableProduct(size_t num, double cost, std::string status) : Product(num, cost), taxstatus(status){
      taxStatusArray[HST] = 0.13; // 13 %
      taxStatusArray[PST] = 0.08;  // 8 %
    }
    virtual double getCharge() const
    {
      double charge = 0.0L;

      if (taxstatus == "HST")
        charge = Product::getCharge() + Product::getCharge()*taxStatusArray[HST];
      else
        charge = Product::getCharge() + Product::getCharge()*taxStatusArray[PST];

      return charge;
    }
    virtual void display(std::ostream& os) const
    {
      Product::display(os);
      os << " " << this->taxstatus;
    }
    void setTaxStatus(std::string tax)
    {
      this->taxstatus = tax;
    }
  };

  // displays a single line 
  std::ostream& operator<<(std::ostream& os, const iProduct& prd)
  {
    prd.display(os);
    return os;
  }

  // Receives a reference to the input file stream, 
  // reads the next record from the stream, allocates 
  // memory for the corresponding iProduct object
  iProduct* readProduct(std::ifstream& ins)
  {
    std::string line;
    std::getline(ins, line);
    if(VERBOSE) std::cout << "Line -->" << line << "<--" << std::endl;

    if (line.find("H") != std::string::npos || line.find("P") != std::string::npos)
    {
      size_t i = 0;
      // set the number of product
      std::string numstr = "";
      for (; i < line.size() && line[i] != ' '; i++) numstr += line[i];
      if (VERBOSE) std::cout << "number[" << numstr << "]";
      i++;
      // set the cost of product
      std::string coststr = "";
      for (; i < line.size() && line[i] != ' '; i++) coststr += line[i];
      if (VERBOSE) std::cout << "cost[" << coststr << "]";
      i++;
      // set the status of product
      std::string statusstr = "";
      for (; i < line.size() && line[i] != '\n'; i++) statusstr += line[i];
      if (statusstr == "H") statusstr = "HST";
      else statusstr = "PST";
      if (VERBOSE) std::cout << "taxstatus[" << statusstr << "]\n";

      iProduct* prd = new TaxableProduct(std::stoi(numstr), std::stod(coststr), statusstr);

      return prd;
    }
    else
    {
      size_t i = 0;
      // set the number of product
      std::string numstr = "";
      for (; i < line.size() && line[i] != ' '; i++) numstr += line[i];
      if (VERBOSE) std::cout << "number[" << numstr << "]";
      i++;
      // set the cost of product
      std::string coststr = "";
      for (; i < line.size() && (line[i] != ' ' || line[i] != '\n'); i++) coststr += line[i];
      if (VERBOSE) std::cout << "cost[" << coststr << "]\n";

      iProduct* prd = new Product(std::stoi(numstr), std::stod(coststr));

      return prd;
    }
  }
}
#endif

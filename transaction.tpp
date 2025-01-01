#include "transaction.h"

template <typename IDType, typename PriceType>
Transaction<IDType, PriceType>::Transaction(const IDType &id, char t, int qty, PriceType pr)
    : orderID(id), type(t), quantity(qty), price(pr) {}

template <typename IDType, typename PriceType>
IDType Transaction<IDType, PriceType>::getOrderID() const {
    return orderID;
}

template <typename IDType, typename PriceType>
char Transaction<IDType, PriceType>::getType() const {
    return type;
}

template <typename IDType, typename PriceType>
int Transaction<IDType, PriceType>::getQuantity() const {
    return quantity;
}

template <typename IDType, typename PriceType>
PriceType Transaction<IDType, PriceType>::getPrice() const {
    return price;
}

type t = {
    bought: list(Product.t),
    milks: list(Milk.t),
    money: int,
}

let make = () => {
    bought: [],
    milks: [],
    money: 100,
};

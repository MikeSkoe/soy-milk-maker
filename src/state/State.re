type gameState = {
    bought: list(Product.t),
    milks: list(Milk.t),
    money: int,
};

type t =
    | Game(gameState)
    | Menu;

let make = () => Game({
    bought: [],
    milks: [],
    money: 100,
});

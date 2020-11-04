type gameState = {
    bought: list(Product.t),
    milks: list(Milk.t),
    money: int,
};

let makeGameState = (): gameState => ({
    bought: [],
    milks: [],
    money: 150,
})

type t =
    | Game(gameState)
    | Menu;

let make = () => Game(makeGameState());

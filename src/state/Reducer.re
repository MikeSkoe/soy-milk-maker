type action =
    | Tick
    | Buy(Product.t)
    | Sell(Milk.t)
    | Restart;

let tick = (state: State.gameState): State.gameState => ({
    ...state,
    milks: List.map((milk: Milk.t): Milk.t => {...milk, time: milk.time +. 0.1}, state.milks),
});

let buy_product = (
    state: State.gameState,
    product,
): State.gameState => switch (
    state.milks |> List.exists((milk: Milk.t) => milk.source == product),
    state.money >= Product.price_of_product(product),
) {
    | (false, true) => ({
        ...state,
        money: state.money - Product.price_of_product(product),
        milks: state.milks @ [Milk.make(~source=product, ())],
    })
    | (_, _) => state
};

let sell_milk = (state: State.gameState, milk: Milk.t): State.gameState => ({
    ...state,
    money: state.money
        + Milk.price_of_milk(milk),
    milks: state.milks
        |> List.filter((m: Milk.t) => m.source !== milk.source)
});

let reducer = (state: State.t, action) => switch state {
    | Menu => state
    | Game(gameState) => switch action {
        | Tick => Game(tick(gameState))
        | Buy(product) => Game(buy_product(gameState, product))
        | Sell(milk) => Game(sell_milk(gameState, milk))
        | Restart => State.make()
    };
};

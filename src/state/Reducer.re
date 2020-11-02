type action =
    | Tick
    | Buy(Product.t)
    | Sell(Milk.t)
    | Restart;

let tick = (state: State.t): State.t => {
    ...state,
    milks: state.milks
        |> List.map((milk: Milk.t): Milk.t => {...milk, time: milk.time +. 0.1}),
};

let buy_product = (
    state: State.t,
    product,
) => switch (
    state.milks |> List.exists((milk: Milk.t) => milk.source == product, ),
    state.money >= Product.price_of_product(product),
) {
    | (false, true) => {
        ...state,
        money: state.money - Product.price_of_product(product),
        milks: state.milks @ [Milk.make(~source=product, ())],
    }
    | (_, _) => state
}

let sell_milk = (state: State.t, milk: Milk.t) => {
    ...state,
    money: state.money
        + Milk.price_of_milk(milk),
    milks: state.milks
        |> List.filter((m: Milk.t) => m.source !== milk.source)
}

let reducer = (state: State.t) => fun
    | Tick => tick(state)
    | Buy(product) => buy_product(state, product)
    | Sell(milk) => sell_milk(state, milk)
    | Restart => State.make();

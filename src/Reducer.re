type action =
    | Tick
    | Buy(State.product)
    | Sell(State.milk)
    | Restart;

let tick = (state: State.t): State.t => {
    ...state,
    milks: state.milks
        |> List.map((milk: State.milk): State.milk => {...milk, time: milk.time +. 0.1}),
};

let buy_product = (
    state: State.t,
    product,
) => switch (
    state.milks |> List.exists((milk: State.milk) => milk.source == product, ),
    state.money >= State.price_of_product(product),
) {
    | (false, true) => {
        ...state,
        money: state.money - State.price_of_product(product),
        milks: state.milks @ [State.makeMilk(~source=product, ())],
    }
    | (_, _) => state
}

let sell_milk = (state: State.t, milk: State.milk) => {
    ...state,
    money: state.money
        + State.price_of_milk(milk),
    milks: state.milks
        |> List.filter((m: State.milk) => m.source !== milk.source)
}

let reducer = (state: State.t) => fun
    | Tick => tick(state)
    | Buy(product) => buy_product(state, product)
    | Sell(milk) => sell_milk(state, milk)
    | Restart => State.make();

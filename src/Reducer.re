type action =
    | Tick
    | Buy(State.product)
    | Cell(State.milk);

let tick = (state: State.t): State.t => {
    ...state,
    milks: state.milks
        |> List.map((milk: State.milk): State.milk => {...milk, time: milk.time + 1}),
};

let buy_product = (state: State.t, product) => {
    ...state,
    money: state.money - State.price_of_product(product),
    milks: state.milks @ [State.makeMilk(~source=product, ())],
};

let cell_milk = (state: State.t, milk: State.milk) => {
    ...state,
    money: state.money + State.price_of_milk(milk),
    milks: state.milks
        |> List.filter((m: State.milk) => m.source !== milk.source)
}

let reducer = (state: State.t) => fun
    | Tick => tick(state)
    | Buy(product) => buy_product(state, product)
    | Cell(milk) => cell_milk(state, milk);

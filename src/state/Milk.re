type t = {
    source: Product.t,
    time: float,
    id: int,
};

type milkState =
    | Preparing
    | Good
    | Bad;

let state_of_milk = fun
    | {time} when time < 20.0 => Preparing
    | {time} when time > 60.0 => Bad
    | _ => Good;

let make = (~source, ~time=0.0, ~id=Random.int(999), ()) =>  {source, time, id}

let profit_of_milk = milk => switch (state_of_milk(milk)) {
    | Preparing => -Product.price_of_product(milk.source)
    | Good => milk.time |> int_of_float
    | Bad => -(Product.price_of_product(milk.source) * 2)
};

let price_of_milk = milk => {
    let profit = profit_of_milk(milk);
    let productPrice = Product.price_of_product(milk.source);

    profit + productPrice;
};

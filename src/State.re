type product =
    | Soy
    | Nut
    | Coconut;

type milk = {
    source: product,
    time: float,
};

type milkState =
    | Preparing
    | Good
    | Bad;

let state_of_milk = fun
    | {time} when time < 20.0 => Preparing
    | {time} when time > 60.0 => Bad
    | _ => Good;

let makeMilk = (~source, ~time=0.0, ()) =>  {source, time}

type t = {
    bought: list(product),
    milks: list(milk),
    money: int,
}

let make = () => {
    bought: [],
    milks: [],
    money: 100,
};

let price_of_product = fun
    | Soy => 50
    | Nut => 100
    | Coconut => 150;

let string_of_product = fun
    | Soy => "soy"
    | Nut => "nut"
    | Coconut => "coconut";

let profit_of_milk = milk => switch (state_of_milk(milk)) {
    | Preparing => -price_of_product(milk.source)
    | Good => milk.time |> int_of_float
    | Bad => -(price_of_product(milk.source) * 2)
};

let price_of_milk = milk => {
    let profit = profit_of_milk(milk);
    let productPrice = price_of_product(milk.source);

    profit + productPrice;
};

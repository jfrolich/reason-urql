open ReasonUrql;
open Hooks;
open PokemonStyles;

module GetPokemon = [%graphql
  {|
  query pokemon($name: String!, $id: String!) {
    pokemon(name: $name, id: $id) {
      name
      classification
      height {
        maximum
      }
      weight {
        maximum
      }
      image
    }
  }
|}
];

[@react.component]
let make = (~pokemon: string) => {
  let ({response}, _) =
    useQuery(GetPokemon.definition, ~id="1", ~name=pokemon, ());

  switch (response) {
  | Data(data) =>
    switch (data##pokemon) {
    | Some(pokemon) =>
      switch (
        pokemon##image,
        pokemon##classification,
        pokemon##name,
        pokemon##height,
        pokemon##weight,
      ) {
      | (
          Some(image),
          Some(classification),
          Some(name),
          Some(height),
          Some(weight),
        ) =>
        <section className=Styles.dexContainer>
          <div className=Styles.dex>
            <div className=Styles.dexImageContainer>
              <img className=Styles.dexImage src=image />
            </div>
            <div className=Styles.dexText>
              <h1 className=Styles.dexTitle> name->React.string </h1>
              <h2 className=Styles.dexSubTitle>
                classification->React.string
              </h2>
              {switch (height##maximum, weight##maximum) {
               | (Some(heightMax), Some(weightMax)) =>
                 <div className=Styles.dexGrid>
                   <p> {("Height: " ++ heightMax)->React.string} </p>
                   <p> {("Weight: " ++ weightMax)->React.string} </p>
                 </div>
               | (_, _) => React.null
               }}
            </div>
          </div>
        </section>
      | (_, _, _, _, _) => React.null
      }
    | None => React.null
    }
  | Fetching => <div> "Loading"->React.string </div>
  | Error(e) => <div> e.message->React.string </div>
  | NotFound => <div> "Not Found"->React.string </div>
  };
};

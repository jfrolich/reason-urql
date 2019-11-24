let useMutation:
  (~request: UrqlTypes.request('response)) =>
  (
    UrqlTypes.hookResponse('response, 'extensions),
    option(UrqlClient.ClientTypes.partialOperationContext) =>
    Js.Promise.t(UrqlClient.ClientTypes.operationResult),
  );

let useDynamicMutation:
  (~query: string, ~parse: Js.Json.t => 'response) =>
  (
    UrqlTypes.hookResponse('response, 'extensions),
    (
      {.. "variables": Js.Json.t},
      option(UrqlClient.ClientTypes.partialOperationContext)
    ) =>
    Js.Promise.t(UrqlClient.ClientTypes.operationResult),
  );

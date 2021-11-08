- Service Types:
	- Data service (connects to a data source, like a database, files, etc.)
	- Business service (ex. order domain)
	- Translation service (ex. email sending service)
	- Edge service (serving data to users, ex. make the app more mobile friendly)

- Platform:
	- Runtime for services (bare-metal servers, VMs, kubernetes, etc.)
	- Ancillary services (you don't write, but you use, like auth. servers, etc.)
	- Operational components (log aggregators, shippers, etc.)
	- Diagnostic components (connect and diagnose problems)

- Cloud native:
	- Microservices do not make a system cloud native
	- Cloud native does not require microservices
	- Cloud native is an architectural style
	- It is designed to faciliate operating in the cloud
	- 12 factor application development
	- Portable and scalable apps
	- Can be run in a single datacenter

- Microservice:
	- It doesn't have a clear definition (ex. nano service)
	- Smaller scoped units of work
	- Breaking into small units of work
	- Focuses on data, business or function domains
	- They can scale independently
	- Not monolithic service artifacts

- Microservice + cloud native benefits:
	- Scalability
	- Can run one without the other
	- Distinct concepts, often considered the same

Decomposition of a system
- Functional use patterns:
	- Domain based (domain boundaries, can be broken down)
	- Business process based
	- Atomic transaction based
- Strategies:
	- Strangler pattern (most common pattern, breaking down monoliths)
	- Sidecar pattern (offload forces into separate components, deployed next to a component)

Domain based:
- Data domain based decomposition:
	- We use this one th most
	- Driven by the data domain model itself
	- Underlying schema is not important
	- Focuses on data patterns
	- Domain-driven design
	- Start with a model, not the datastore (database)
	- Evaluate actions (what needs to be done)
	- Build the service, contract first

Business process based:
- Business process domains:
	- Provide higher-level business functionality
	- Allows you to encapsulate related domains
	- No datasource access
	- Distinct functional uses
	- Identify the process (you have the data before you start)
	- Identify the domains
	- Define the API (focus on the contract, not on the models)
	- Wire the service

- Atomic transaction based:
	- Guarantee atomicity, consistency, isolation, durability (ACID) transactions
	- Provide failure domains and rollbacks
	- Force blocking until commit
	- Don't use distributed transactions
	- Ensure you must have the atomic service
	- Domains must be in a shared database
	- Clearly get the transaction defined, including rollback conditions
	- Implement the service as normal, with fast fail and rollback

- Strangler pattern:
	- Break a monolith up by strangling the dependency on it
	- Can be top down
	- Can be bottom up
	- Carving out the functionality

- Sidecar pattern:
	- Determine the process (write to process specific enough)
	- Build the sidecar
	- Schedule it to deploy with the appropriate services
	- Functionality appears without embedding it

- API gateway/Gateway pattern:
	- Problem: Client ability to call any service can create chaos
	- Gateway provides a facade/proxy
	- Single layer that proxies, mutates, or limits calls
	- Can become a single point of failure
- Mutation behaviors:
	- Can simply proxy (restrict based on the access of the client)
	- Can decorate
	- Can aggregate (assembles the calls into a single payload)
	- Can limit access
	- Movement buffer
- Strategy:
	- Define contracts
	- Expose APIs for those contracts, client focused
	- Adhere to strict version control and passive changes only (semantic versioning)
	- Implement the gateway to call your services and your clients to call the gateway

- Process aggregator:
	- Problem: You have several business processes that must be called together
and have a composite payload
	- Aggregator provides clients a single API to call (DRY principle)
	- Can introduce its own processing logic
	- Can cause long blocking calls (very long running processes), use async patterns instead
- Design:
	- Determine the business processes
	- Determine the processing rules
	- Design a consolidated model
	- Design an API for the actions on that model
	- Wire the service together and implement the internal processing
	- Abstraction for the sake of abstraction does no good

- Edge pattern:
	- Problem: Client use varies by platform and scaling a gateway presents wasted resources or
clients need special business logic
	- Client-specific "gateways"
	- Focusing on isolating calls for client systems
- Design:
	- Identify the client
	- Build contracts
	- Implement contracts
	- Maintain passivity as long as client is needed
- Gateway vs. Edge:
	- Similar, but different (edge preferred)
	- Edge targets clients
	- Edge is more scalable
	- Edge is more flexible for new clients
	- Gateway has less moving parts

- Single service database pattern:
	- Single service, single database
	- Problem: scalability needs between database and service are related
	- Each service implementation gets its own datastore
	- Datastore distributes with the service
	- Datastore scales proportionally to the service
	

- Shared service database pattern:
	- All data domains exist within a single database
	- Data distribution should be handled by the database
	- Break data domains into schemas or similar constructs
	- Users don't span schemas

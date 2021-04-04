### Kubectl commands

#### Get resource (service/pod/deloyment/node/crd)
- kubectl get [resource]
#### Get all namespaces for the pods
- kubectl get pods --all-namespaces
#### Describe resource information
- kubectl describe [resource]
#### Get information about different fields
- kubectl explain pod.spec.restartPolicy
#### Apply configuration
- kubectl apply -f (file or folder) [target]
#### Apply kustomization.yml
- kubectl apply -k (kustomization.yml) [target]
#### View the difference between the given file and the currently applied config
- kubectl diff -f [filename]
#### Edit a specified resource
- kubectl edit [resource] [name]
#### View logs of a pod
- kubectl logs [name]
#### View logs using label selector
- kubectl logs -l app=blue-green
#### Expose port
- kubectl expose pod green --port 8080 --name blue-green
#### Delete resource
- kubectl delete [resource] [name]
#### Port forwarding
- kubectl port-forward [pod] [from]:[to]
#### Exec into pod
- kubectl exec -it [name] [command]
#### Exec into pod with a different namespace
- kubectl exec -n [namespace] -it [name] -- [command]
#### View pod metrics
- kubectl top [name]
#### View the current kubernetes API definition
- kubectl api-resources
#### Creating a ConfigMap from a file
- kubectl create configmap [name] --from-file=[filename]
#### Useful for testing the output of a command
- kubectl [commands] --dry-run -o yaml
#### Create new namespace
- kubectl create namespace [name]
#### Switch to a namespace
- kubectl config set-context --current --namespace=[name]
#### Wait for a pod to  be ready
- kubectl wait --for=condition=Ready pod -l app=[name] -n [namespace]
#### View kustomize config
- kubectl kustomize [directory]

#### Using Krew package manager
#### Debugging a pod
- kubectl debug [name] --attach
#### Viewing the network traffic of a pod
- kubectl sniff [pod]

### Kube specific info:
- Worker nodes are the containers where pods are placed into
- ClusterIP: IP defined in the cluster
- NodePort: where we can access the given node
- Liveness probe: checks if the pod is running, if not, restart it
- Readiness probe: checks if the pod is ready, if not, the pod is stopped
- spec.containers.resources: useful for handling the CPU/memory load (also check the vertical pod autoscaler)

#### Affinity/anti-affinity
- Pod affinity:
  - when set, it will find the pod using this labelSelector and makes sure that the topologyKey is the same for both
- Pod anti-affinity: useful for placing pods into separate nodes
  - when the node crashes, the new pod will be placed into a separate node
  - specified with the topologySpreadConstraints
  - maxSkew: 1 keeps the nodes together as close as possible
- Node affinity:
  - useful when special resources are needed (like more GPU power in case of TensorFlow)
- Node anti-affinity:
  - useful for keeping the pods off the node that has special resources (don't run webserver pods on a node that is used for ML)
  
#### Horizontal pod autoscaler (HPA)
- Used by setting scaleTargetRef, minReplicas, maxReplicas and metrics (CPU utilization)
- Scaling up and down the pods
- Custom metrics/Prometheus for watching latency, etc.

#### ConfigMaps
- Used for passing environmental variables

#### Secrets
- Can be used by adding them as volumes
- Never written to the disk
- Has multiple types:
  - Generic
  - TLS secret (keys, certificates)
  
#### Network security
- kind: NetworkPolicy
- Pods can be configured which other pods they can talk with
- Check podSelector and policyTypes

#### Role based-access control
- By "default" accounts can only read all objects, but not write
- kind: ServiceAccount and specified with spec.serviceAccount
- kind: Role (can read from pods), ClusterRole (can read from nodes)
- kind: RoleBinding, ClusterBinding are used to bind the roles to accounts
  - roleRef gets the roles from the previously specified role
  
#### Namespaces
- One flat layer of namespaces
- Kubernetes internal system components are in the "kube-system" namespace
- kubens is useful for dispalying the current namespace and switching between namespaces

#### Multiple containers in a pod (sidecar)
- One shared IP address for the Pod
- Services meshes (Linkerd):
  - linkerd dashboard
- Useful if we have a separate container from the app that we are running (ex. logging, transforming objects/files)

#### Custom Resource Definition (CRD)
- Add new types to kubernetes
- Operators (OperatorHub.io)

#### Helm
- Version 3 are more stable
- Useful for maintaining yaml files by creating multiple template files
- Helm Chart:
  - Usually only one chart is created for all templates
  - Provide values for the template files (useful for different environments)
- helm install -f [filename] [name] [directory]
- helm upgrade -f [filename] [name] [directory]
- helm history [name]

#### Kustomize
- Useful for patching yaml files

#### Debugging
- A pod with no images can be debugged with a sidecar (if one exists)
- We can attach a temporary debugging container to a pod
- Debug shell pod in the cluster (--image=nixery.dev/shell also you can add more commands like /curl/wget etc.)

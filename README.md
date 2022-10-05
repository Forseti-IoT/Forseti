# Forseti
A cross-platform delegation solution for IoT leasing.

* App: A application for user to delegate permission and controll devices.
* Platform: A IoT platform demo about how to integrate Forseti into existing platforms.
* zkp: Forseti's encryption moudule. It includes the prove and verifcation model for permission authentication and transfer.
* blockchain: Forseti's consensus module. It includes smart contract and the http api to call the smart contract

In this poject, we take Philips Bulb to describe how to integrate Forseti into its origional platform design.

## Dependency
* Zero-knowledge Proof:ZKBoo and its dependency
https://github.com/Sobuno/ZKBoo

* Decentralized Ledger: Hyperledger Fabric (v2.2 LTS) and its dependency
You need to deploy the ledger by yourselves to run this project.
https://hyperledger-fabric.readthedocs.io/en/release-2.2/


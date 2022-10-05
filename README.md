# Forseti
A cross-platform delegation solution for IoT leasing.

* App: A application for users to delegate permission and control devices.
* Platform: A IoT platform demo about how to integrate Forseti into existing platforms.
* zkp: Forseti's encryption module. It includes the prove and verify process for permission authentication and transfer.
* blockchain: Forseti's consensus module. It includes a smart contract and the HTTP API to call the smart contract

In this project, we take Philips Bulb to describe how to integrate Forseti into its original platform design.

## Dependency
* Zero-knowledge Proof: ZKBoo and its dependency
https://github.com/Sobuno/ZKBoo

* Decentralized Ledger: Hyperledger Fabric (v2.2 LTS) and its dependency
https://hyperledger-fabric.readthedocs.io/en/release-2.2/

    You need to deploy the ledger by yourselves to run this project.




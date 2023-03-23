#include <retesteth/unitTests/testSuites.h>
using namespace std;

namespace test::unittests
{

string const c_sampleStateTestFiller = R"({
    "add11" : {
        "_info" : {
            "comment" : "A test for (add 1 1) opcode result"
        },
        "env" : {
             "currentCoinbase" : "2adc25665018aa1fe0e6bc666dac8fc2697ff9ba",
             "currentDifficulty" : "0x20000",
             "currentGasLimit" : "0xFF112233445566",
             "currentNumber" : "1",
             "currentTimestamp" : "1000",
             "previousHash" : "5e20a0453cecd065ea59c37ac63e079ee08998b6045136a8ce6635c7912ec0b6"
        },
       "expect" : [
       {
           "indexes" : { "data" : -1, "gas" : -1, "value" : -1 },
           "network" : [">=Berlin", "Berlin+1153"],
           "result" : {
               "095e7baea6a6c7c4c2dfeb977efac326af552d87" : {
                   "code" : "0x600160010160005500",
                   "storage" : {
                       "0x00" : "0x02"
                  }
               },
               "2adc25665018aa1fe0e6bc666dac8fc2697ff9ba" : {
                   "nonce" : "1"
               },
               "a94f5374fce5edbc8e2a8697c15331677e6ebf0b" : {
                   "code" : "0x",
                   "nonce" : "1",
                   "storage" : {
                   }
               },
               "e94f5374fce5edbc8e2a8697c15331677e6ebf0b" : {
                   "shouldnotexist" : "1"
               }
           }
       }
       ],
       "pre" : {
           "2adc25665018aa1fe0e6bc666dac8fc2697ff9ba" : {
               "balance" : "0",
               "code" : "0x",
               "nonce" : "1",
               "storage" : {
               }
           },
           "095e7baea6a6c7c4c2dfeb977efac326af552d87" : {
               "balance" : "1000000000000000000",
               "code" : "0x600160010160005500",
               "code" : "{ [[0]] (ADD 1 1) }",
               "nonce" : "0",
               "storage" : {
               }
           },
           "a94f5374fce5edbc8e2a8697c15331677e6ebf0b" : {
               "balance" : "1000000000000000000",
               "code" : "0x",
               "nonce" : "0",
               "storage" : {
               }
           }
       },
       "transaction" : {
          "data" : [
               ""
           ],
          "gasLimit" : [
               "400000"
          ],
         "gasPrice" : "10",
         "nonce" : "0",
         "secretKey" : "45a915e4d060149eb4365960e6a7a45f334393093061116b197e3240065ff2d8",
         "to" : "095e7baea6a6c7c4c2dfeb977efac326af552d87",
         "value" : [
             "100000"
         ]
       }
  }
})";


string const c_sampleStateTestFilled = R"({
    "add11" : {
        "_info" : {
            "comment" : "A test for (add 1 1) opcode result",
            "filling-rpc-server" : "evm version 1.11.4-unstable-e14043db-20230308",
            "filling-tool-version" : "retesteth-0.3.0-shanghai+commit.fd2c0a83.Linux.g++",
            "generatedTestHash" : "b33fbe39b474b9d63fe4e2e493a997818c4d3b33c9dc085954d482ecf3db6da9",
            "lllcversion" : "Version: 0.5.14-develop.2022.7.30+commit.a096d7a9.Linux.g++",
            "solidity" : "Version: 0.8.17+commit.8df45f5f.Linux.g++",
            "source" : "src/GeneralStateTestsFiller/stExample/add11Filler.json",
            "sourceHash" : "7b59a4d0c6180797011b0181ebe84680e9d18a6d38db8a740850a596cfc6b148"
        },
        "env" : {
            "currentBaseFee" : "0x0a",
            "currentCoinbase" : "0x2adc25665018aa1fe0e6bc666dac8fc2697ff9ba",
            "currentDifficulty" : "0x020000",
            "currentGasLimit" : "0xff112233445566",
            "currentNumber" : "0x01",
            "currentRandom" : "0x0000000000000000000000000000000000000000000000000000000000020000",
            "currentTimestamp" : "0x03e8",
            "previousHash" : "0x5e20a0453cecd065ea59c37ac63e079ee08998b6045136a8ce6635c7912ec0b6"
        },
        "post" : {
            "Berlin" : [
                {
                    "hash" : "0xcd39e0cdd18f8f811911222ae6779341663d0293e1a3d9501da7ac2f4da9b277",
                    "indexes" : {
                        "data" : 0,
                        "gas" : 0,
                        "value" : 0
                    },
                    "logs" : "0x1dcc4de8dec75d7aab85b567b6ccd41ad312451b948a7413f0a142fd40d49347",
                    "txbytes" : "0xf863800a83061a8094095e7baea6a6c7c4c2dfeb977efac326af552d87830186a0801ba0ffb600e63115a7362e7811894a91d8ba4330e526f22121c994c4692035dfdfd5a06198379fcac8de3dbfac48b165df4bf88e2088f294b61efb9a65fe2281c76e16"
                }
            ],
            "London" : [
                {
                    "hash" : "0xe8010ce590f401c9d61fef8ab05bea9bcec24281b795e5868809bc4e515aa530",
                    "indexes" : {
                        "data" : 0,
                        "gas" : 0,
                        "value" : 0
                    },
                    "logs" : "0x1dcc4de8dec75d7aab85b567b6ccd41ad312451b948a7413f0a142fd40d49347",
                    "txbytes" : "0xf863800a83061a8094095e7baea6a6c7c4c2dfeb977efac326af552d87830186a0801ba0ffb600e63115a7362e7811894a91d8ba4330e526f22121c994c4692035dfdfd5a06198379fcac8de3dbfac48b165df4bf88e2088f294b61efb9a65fe2281c76e16"
                }
            ],
            "Merge" : [
                {
                    "hash" : "0xe8010ce590f401c9d61fef8ab05bea9bcec24281b795e5868809bc4e515aa530",
                    "indexes" : {
                        "data" : 0,
                        "gas" : 0,
                        "value" : 0
                    },
                    "logs" : "0x1dcc4de8dec75d7aab85b567b6ccd41ad312451b948a7413f0a142fd40d49347",
                    "txbytes" : "0xf863800a83061a8094095e7baea6a6c7c4c2dfeb977efac326af552d87830186a0801ba0ffb600e63115a7362e7811894a91d8ba4330e526f22121c994c4692035dfdfd5a06198379fcac8de3dbfac48b165df4bf88e2088f294b61efb9a65fe2281c76e16"
                }
            ],
            "Shanghai" : [
                {
                    "hash" : "0xe8010ce590f401c9d61fef8ab05bea9bcec24281b795e5868809bc4e515aa530",
                    "indexes" : {
                        "data" : 0,
                        "gas" : 0,
                        "value" : 0
                    },
                    "logs" : "0x1dcc4de8dec75d7aab85b567b6ccd41ad312451b948a7413f0a142fd40d49347",
                    "txbytes" : "0xf863800a83061a8094095e7baea6a6c7c4c2dfeb977efac326af552d87830186a0801ba0ffb600e63115a7362e7811894a91d8ba4330e526f22121c994c4692035dfdfd5a06198379fcac8de3dbfac48b165df4bf88e2088f294b61efb9a65fe2281c76e16"
                }
            ]
        },
        "pre" : {
            "0x095e7baea6a6c7c4c2dfeb977efac326af552d87" : {
                "balance" : "0x0de0b6b3a7640000",
                "code" : "0x600160010160005500",
                "nonce" : "0x00",
                "storage" : {
                }
            },
            "0x2adc25665018aa1fe0e6bc666dac8fc2697ff9ba" : {
                "balance" : "0x00",
                "code" : "0x",
                "nonce" : "0x01",
                "storage" : {
                }
            },
            "0xa94f5374fce5edbc8e2a8697c15331677e6ebf0b" : {
                "balance" : "0x0de0b6b3a7640000",
                "code" : "0x",
                "nonce" : "0x00",
                "storage" : {
                }
            }
        },
        "transaction" : {
            "data" : [
                "0x"
            ],
            "gasLimit" : [
                "0x061a80"
            ],
            "gasPrice" : "0x0a",
            "nonce" : "0x00",
            "secretKey" : "0x45a915e4d060149eb4365960e6a7a45f334393093061116b197e3240065ff2d8",
            "sender" : "0xa94f5374fce5edbc8e2a8697c15331677e6ebf0b",
            "to" : "0x095e7baea6a6c7c4c2dfeb977efac326af552d87",
            "value" : [
                "0x0186a0"
            ]
        }
    }
})";

}

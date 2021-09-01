#include "StateTestFillerTransaction.h"
#include <retesteth/EthChecks.h>
#include <retesteth/TestHelper.h>
#include <retesteth/testStructures/Common.h>

namespace test
{
namespace teststruct
{
StateTestFillerTransaction::StateTestFillerTransaction(spDataObjectMove _data)
{
    try
    {
        m_rawData = _data.getPointer();

        if (m_rawData->count("maxFeePerGas") || m_rawData->count("maxPriorityFeePerGas"))
        {
            REQUIRE_JSONFIELDS(m_rawData, "StateTestFillerTransaction " + m_rawData->getKey(),
                {{"data", {{DataType::Array}, jsonField::Required}},
                    {"gasLimit", {{DataType::Array}, jsonField::Required}},
                    {"nonce", {{DataType::String}, jsonField::Required}},
                    {"value", {{DataType::Array}, jsonField::Required}},
                    {"to", {{DataType::String}, jsonField::Required}},
                    {"maxFeePerGas", {{DataType::String}, jsonField::Required}},
                    {"maxPriorityFeePerGas", {{DataType::String}, jsonField::Required}},
                    {"secretKey", {{DataType::String}, jsonField::Required}}});
        }
        else
        {
            // LEGACY TRANSACTION TEMPLATE (gtest FILLER)
            REQUIRE_JSONFIELDS(m_rawData, "StateTestFillerTransaction " + m_rawData->getKey(),
                {{"data", {{DataType::Array}, jsonField::Required}},
                    {"gasLimit", {{DataType::Array}, jsonField::Required}},
                    {"gasPrice", {{DataType::String}, jsonField::Required}},
                    {"nonce", {{DataType::String}, jsonField::Required}},
                    {"value", {{DataType::Array}, jsonField::Required}},
                    {"to", {{DataType::String}, jsonField::Required}},
                    {"secretKey", {{DataType::String}, jsonField::Required}}});
        }

        // Read data from JSON in test filler
        // The VALUE fields can be decimal -> convert it to hex
        // The data field can be LLL or other code -> compile it to BYTES
        (*m_rawData).performModifier(mod_valueToCompactEvenHexPrefixed, {"data", "to", "secretKey"});
        if (m_rawData->count("secretKey"))
            (*m_rawData).atKeyUnsafe("secretKey").performModifier(mod_valueInsertZeroXPrefix);

        if (m_rawData->atKey("to").asString().empty())
            m_creation = true;
        else
        {
            m_creation = false;
            (*m_rawData).atKeyUnsafe("to").performModifier(mod_valueInsertZeroXPrefix);
            m_to = spFH20(new FH20(m_rawData->atKey("to")));
        }

        m_secretKey = spFH32(new FH32(m_rawData->atKey("secretKey")));
        m_nonce = spVALUE(new VALUE(m_rawData->atKey("nonce")));

        for (auto& el : (*m_rawData).atKeyUnsafe("data").getSubObjectsUnsafe())
        {
            spDataObject dataInKey;
            spAccessList accessList;
            if (el->type() == DataType::Object)
            {
                REQUIRE_JSONFIELDS(el, "StateTestFillerTransaction::dataWithList " + m_rawData->getKey(),
                    {{"data", {{DataType::String}, jsonField::Required}},
                     {"accessList", {{DataType::Array}, jsonField::Required}}});

                dataInKey = (*el).atKeyPointerUnsafe("data");
                accessList = spAccessList(new AccessList(el->atKey("accessList")));
            }
            else
                dataInKey = el;

            // -- Compile LLL in transaction data into byte code if not already
            // (*dataInKey).setKey("`data` array element in General Transaction Section");  // Hint
            // Detect :label prefix over code compilation

            string label;
            string rawData = dataInKey->asString();
            std::string const c_labelPrefix = ":label";
            if (rawData.find(c_labelPrefix) != string::npos)
            {
                size_t const pos = rawData.find(c_labelPrefix);
                size_t const posEnd = rawData.find(' ', pos + c_labelPrefix.size() + 1);
                if (posEnd != string::npos)
                {
                    label = rawData.substr(pos, posEnd - pos);
                    rawData = rawData.substr(posEnd + 1);  // remove label before code parsing
                }
                else
                {
                    label = rawData.substr(pos);
                    rawData = "";
                }
            }
            (*dataInKey).setString(test::compiler::replaceCode(rawData));
            // ---
            m_databox.push_back(Databox(dataInKey.getContent(), label, rawData.substr(0, 20), accessList));
        }
        for (auto const& el : m_rawData->atKey("gasLimit").getSubObjects())
            m_gasLimit.push_back(el.getCContent());
        for (auto const& el : m_rawData->atKey("value").getSubObjects())
            m_value.push_back(el.getCContent());

        if (m_rawData->count("maxFeePerGas") || m_rawData->count("maxPriorityFeePerGas"))
        {
            // EIP 1559 TRANSACTION TEMPLATE (gtest FILLER)
            m_maxFeePerGas = spVALUE(new VALUE(m_rawData->atKey("maxFeePerGas")));
            m_maxPriorityFeePerGas = spVALUE(new VALUE(m_rawData->atKey("maxPriorityFeePerGas")));
        }
        else
        {
            // LEGACY TRANSACTION TEMPLATE (gtest FILLER)
            m_gasPrice = spVALUE(new VALUE(m_rawData->atKey("gasPrice")));
        }


        // Prepare data for export (export format is different to import format in this case
        (*m_rawData).performModifier(mod_valueToLowerCase);
        size_t index = 0;
        bool atLeastOneNonNullAccessList = false;
        spDataObject exportDatas(new DataObject());
        spDataObject txAccessListData(new DataObject(DataType::Array));
        for (Databox const& el : m_databox)
        {
            spDataObject elb(new DataObject(el.m_data.asString()));
            (*exportDatas).addArrayObject(elb);
            if (el.m_accessList.isEmpty())
                (*txAccessListData).addArrayObject(spDataObject(new DataObject(DataType::Null)));
            else
            {
                (*txAccessListData).addArrayObject(el.m_accessList->asDataObject());
                atLeastOneNonNullAccessList = true;
            }
            index++;
        }

        (*exportDatas).setKey("data");
        (*m_rawData).atKeyPointer("data") = exportDatas;
        if (atLeastOneNonNullAccessList)
            (*m_rawData).atKeyPointer("accessLists") = txAccessListData;

        if (!m_maxFeePerGas.isEmpty() || !m_maxPriorityFeePerGas.isEmpty())
        {
            if (m_maxFeePerGas.isEmpty() || m_maxPriorityFeePerGas.isEmpty())
                ETH_FAIL_MESSAGE("Must be defined both m_maxFeePerGas and m_maxPriorityFeePerGas!");
            if (!atLeastOneNonNullAccessList)
                ETH_FAIL_MESSAGE("Basefee transaction must have accesslist!");
        }
    }
    catch (std::exception const& _ex)
    {
        throw UpwardsException(string("StateTestFillerTransaction parse error: ") + _ex.what() + "\n" + m_rawData->asJson());
    }
}

}  // namespace teststruct
}  // namespace test

// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file petPubSubTypes.cpp
 * This header file contains the implementation of the serialization functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#include <fastcdr/FastBuffer.h>
#include <fastcdr/Cdr.h>

#include "petPubSubTypes.h"

using SerializedPayload_t = eprosima::fastrtps::rtps::SerializedPayload_t;
using InstanceHandle_t = eprosima::fastrtps::rtps::InstanceHandle_t;

namespace benchmark {
    namespace idl {

        OwnerPubSubType::OwnerPubSubType()
        {
            setName("benchmark::idl::Owner");
            auto type_size = Owner::getMaxCdrSerializedSize();
            type_size += eprosima::fastcdr::Cdr::alignment(type_size, 4); /* possible submessage alignment */
            m_typeSize = static_cast<uint32_t>(type_size) + 4; /*encapsulation*/
            m_isGetKeyDefined = Owner::isKeyDefined();
            size_t keyLength = Owner::getKeyMaxCdrSerializedSize() > 16 ?
                    Owner::getKeyMaxCdrSerializedSize() : 16;
            m_keyBuffer = reinterpret_cast<unsigned char*>(malloc(keyLength));
            memset(m_keyBuffer, 0, keyLength);
        }

        OwnerPubSubType::~OwnerPubSubType()
        {
            if (m_keyBuffer != nullptr)
            {
                free(m_keyBuffer);
            }
        }

        bool OwnerPubSubType::serialize(
                void* data,
                SerializedPayload_t* payload)
        {
            Owner* p_type = static_cast<Owner*>(data);

            // Object that manages the raw buffer.
            eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->max_size);
            // Object that serializes the data.
            eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN, eprosima::fastcdr::Cdr::DDS_CDR);
            payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

            try
            {
                // Serialize encapsulation
                ser.serialize_encapsulation();
                // Serialize the object.
                p_type->serialize(ser);
            }
            catch (eprosima::fastcdr::exception::Exception& /*exception*/)
            {
                return false;
            }

            // Get the serialized length
            payload->length = static_cast<uint32_t>(ser.getSerializedDataLength());
            return true;
        }

        bool OwnerPubSubType::deserialize(
                SerializedPayload_t* payload,
                void* data)
        {
            try
            {
                // Convert DATA to pointer of your type
                Owner* p_type = static_cast<Owner*>(data);

                // Object that manages the raw buffer.
                eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->length);

                // Object that deserializes the data.
                eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN, eprosima::fastcdr::Cdr::DDS_CDR);

                // Deserialize encapsulation.
                deser.read_encapsulation();
                payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

                // Deserialize the object.
                p_type->deserialize(deser);
            }
            catch (eprosima::fastcdr::exception::Exception& /*exception*/)
            {
                return false;
            }

            return true;
        }

        std::function<uint32_t()> OwnerPubSubType::getSerializedSizeProvider(
                void* data)
        {
            return [data]() -> uint32_t
                   {
                       return static_cast<uint32_t>(type::getCdrSerializedSize(*static_cast<Owner*>(data))) +
                              4u /*encapsulation*/;
                   };
        }

        void* OwnerPubSubType::createData()
        {
            return reinterpret_cast<void*>(new Owner());
        }

        void OwnerPubSubType::deleteData(
                void* data)
        {
            delete(reinterpret_cast<Owner*>(data));
        }

        bool OwnerPubSubType::getKey(
                void* data,
                InstanceHandle_t* handle,
                bool force_md5)
        {
            if (!m_isGetKeyDefined)
            {
                return false;
            }

            Owner* p_type = static_cast<Owner*>(data);

            // Object that manages the raw buffer.
            eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(m_keyBuffer),
                    Owner::getKeyMaxCdrSerializedSize());

            // Object that serializes the data.
            eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS);
            p_type->serializeKey(ser);
            if (force_md5 || Owner::getKeyMaxCdrSerializedSize() > 16)
            {
                m_md5.init();
                m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.getSerializedDataLength()));
                m_md5.finalize();
                for (uint8_t i = 0; i < 16; ++i)
                {
                    handle->value[i] = m_md5.digest[i];
                }
            }
            else
            {
                for (uint8_t i = 0; i < 16; ++i)
                {
                    handle->value[i] = m_keyBuffer[i];
                }
            }
            return true;
        }

        OwnerV2PubSubType::OwnerV2PubSubType()
        {
            setName("benchmark::idl::OwnerV2");
            auto type_size = OwnerV2::getMaxCdrSerializedSize();
            type_size += eprosima::fastcdr::Cdr::alignment(type_size, 4); /* possible submessage alignment */
            m_typeSize = static_cast<uint32_t>(type_size) + 4; /*encapsulation*/
            m_isGetKeyDefined = OwnerV2::isKeyDefined();
            size_t keyLength = OwnerV2::getKeyMaxCdrSerializedSize() > 16 ?
                    OwnerV2::getKeyMaxCdrSerializedSize() : 16;
            m_keyBuffer = reinterpret_cast<unsigned char*>(malloc(keyLength));
            memset(m_keyBuffer, 0, keyLength);
        }

        OwnerV2PubSubType::~OwnerV2PubSubType()
        {
            if (m_keyBuffer != nullptr)
            {
                free(m_keyBuffer);
            }
        }

        bool OwnerV2PubSubType::serialize(
                void* data,
                SerializedPayload_t* payload)
        {
            OwnerV2* p_type = static_cast<OwnerV2*>(data);

            // Object that manages the raw buffer.
            eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->max_size);
            // Object that serializes the data.
            eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN, eprosima::fastcdr::Cdr::DDS_CDR);
            payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

            try
            {
                // Serialize encapsulation
                ser.serialize_encapsulation();
                // Serialize the object.
                p_type->serialize(ser);
            }
            catch (eprosima::fastcdr::exception::Exception& /*exception*/)
            {
                return false;
            }

            // Get the serialized length
            payload->length = static_cast<uint32_t>(ser.getSerializedDataLength());
            return true;
        }

        bool OwnerV2PubSubType::deserialize(
                SerializedPayload_t* payload,
                void* data)
        {
            try
            {
                // Convert DATA to pointer of your type
                OwnerV2* p_type = static_cast<OwnerV2*>(data);

                // Object that manages the raw buffer.
                eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->length);

                // Object that deserializes the data.
                eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN, eprosima::fastcdr::Cdr::DDS_CDR);

                // Deserialize encapsulation.
                deser.read_encapsulation();
                payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

                // Deserialize the object.
                p_type->deserialize(deser);
            }
            catch (eprosima::fastcdr::exception::Exception& /*exception*/)
            {
                return false;
            }

            return true;
        }

        std::function<uint32_t()> OwnerV2PubSubType::getSerializedSizeProvider(
                void* data)
        {
            return [data]() -> uint32_t
                   {
                       return static_cast<uint32_t>(type::getCdrSerializedSize(*static_cast<OwnerV2*>(data))) +
                              4u /*encapsulation*/;
                   };
        }

        void* OwnerV2PubSubType::createData()
        {
            return reinterpret_cast<void*>(new OwnerV2());
        }

        void OwnerV2PubSubType::deleteData(
                void* data)
        {
            delete(reinterpret_cast<OwnerV2*>(data));
        }

        bool OwnerV2PubSubType::getKey(
                void* data,
                InstanceHandle_t* handle,
                bool force_md5)
        {
            if (!m_isGetKeyDefined)
            {
                return false;
            }

            OwnerV2* p_type = static_cast<OwnerV2*>(data);

            // Object that manages the raw buffer.
            eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(m_keyBuffer),
                    OwnerV2::getKeyMaxCdrSerializedSize());

            // Object that serializes the data.
            eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS);
            p_type->serializeKey(ser);
            if (force_md5 || OwnerV2::getKeyMaxCdrSerializedSize() > 16)
            {
                m_md5.init();
                m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.getSerializedDataLength()));
                m_md5.finalize();
                for (uint8_t i = 0; i < 16; ++i)
                {
                    handle->value[i] = m_md5.digest[i];
                }
            }
            else
            {
                for (uint8_t i = 0; i < 16; ++i)
                {
                    handle->value[i] = m_keyBuffer[i];
                }
            }
            return true;
        }

        OwnerV3PubSubType::OwnerV3PubSubType()
        {
            setName("benchmark::idl::OwnerV3");
            auto type_size = OwnerV3::getMaxCdrSerializedSize();
            type_size += eprosima::fastcdr::Cdr::alignment(type_size, 4); /* possible submessage alignment */
            m_typeSize = static_cast<uint32_t>(type_size) + 4; /*encapsulation*/
            m_isGetKeyDefined = OwnerV3::isKeyDefined();
            size_t keyLength = OwnerV3::getKeyMaxCdrSerializedSize() > 16 ?
                    OwnerV3::getKeyMaxCdrSerializedSize() : 16;
            m_keyBuffer = reinterpret_cast<unsigned char*>(malloc(keyLength));
            memset(m_keyBuffer, 0, keyLength);
        }

        OwnerV3PubSubType::~OwnerV3PubSubType()
        {
            if (m_keyBuffer != nullptr)
            {
                free(m_keyBuffer);
            }
        }

        bool OwnerV3PubSubType::serialize(
                void* data,
                SerializedPayload_t* payload)
        {
            OwnerV3* p_type = static_cast<OwnerV3*>(data);

            // Object that manages the raw buffer.
            eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->max_size);
            // Object that serializes the data.
            eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN, eprosima::fastcdr::Cdr::DDS_CDR);
            payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

            try
            {
                // Serialize encapsulation
                ser.serialize_encapsulation();
                // Serialize the object.
                p_type->serialize(ser);
            }
            catch (eprosima::fastcdr::exception::Exception& /*exception*/)
            {
                return false;
            }

            // Get the serialized length
            payload->length = static_cast<uint32_t>(ser.getSerializedDataLength());
            return true;
        }

        bool OwnerV3PubSubType::deserialize(
                SerializedPayload_t* payload,
                void* data)
        {
            try
            {
                // Convert DATA to pointer of your type
                OwnerV3* p_type = static_cast<OwnerV3*>(data);

                // Object that manages the raw buffer.
                eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->length);

                // Object that deserializes the data.
                eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN, eprosima::fastcdr::Cdr::DDS_CDR);

                // Deserialize encapsulation.
                deser.read_encapsulation();
                payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

                // Deserialize the object.
                p_type->deserialize(deser);
            }
            catch (eprosima::fastcdr::exception::Exception& /*exception*/)
            {
                return false;
            }

            return true;
        }

        std::function<uint32_t()> OwnerV3PubSubType::getSerializedSizeProvider(
                void* data)
        {
            return [data]() -> uint32_t
                   {
                       return static_cast<uint32_t>(type::getCdrSerializedSize(*static_cast<OwnerV3*>(data))) +
                              4u /*encapsulation*/;
                   };
        }

        void* OwnerV3PubSubType::createData()
        {
            return reinterpret_cast<void*>(new OwnerV3());
        }

        void OwnerV3PubSubType::deleteData(
                void* data)
        {
            delete(reinterpret_cast<OwnerV3*>(data));
        }

        bool OwnerV3PubSubType::getKey(
                void* data,
                InstanceHandle_t* handle,
                bool force_md5)
        {
            if (!m_isGetKeyDefined)
            {
                return false;
            }

            OwnerV3* p_type = static_cast<OwnerV3*>(data);

            // Object that manages the raw buffer.
            eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(m_keyBuffer),
                    OwnerV3::getKeyMaxCdrSerializedSize());

            // Object that serializes the data.
            eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS);
            p_type->serializeKey(ser);
            if (force_md5 || OwnerV3::getKeyMaxCdrSerializedSize() > 16)
            {
                m_md5.init();
                m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.getSerializedDataLength()));
                m_md5.finalize();
                for (uint8_t i = 0; i < 16; ++i)
                {
                    handle->value[i] = m_md5.digest[i];
                }
            }
            else
            {
                for (uint8_t i = 0; i < 16; ++i)
                {
                    handle->value[i] = m_keyBuffer[i];
                }
            }
            return true;
        }

        OwnerV4PubSubType::OwnerV4PubSubType()
        {
            setName("benchmark::idl::OwnerV4");
            auto type_size = OwnerV4::getMaxCdrSerializedSize();
            type_size += eprosima::fastcdr::Cdr::alignment(type_size, 4); /* possible submessage alignment */
            m_typeSize = static_cast<uint32_t>(type_size) + 4; /*encapsulation*/
            m_isGetKeyDefined = OwnerV4::isKeyDefined();
            size_t keyLength = OwnerV4::getKeyMaxCdrSerializedSize() > 16 ?
                    OwnerV4::getKeyMaxCdrSerializedSize() : 16;
            m_keyBuffer = reinterpret_cast<unsigned char*>(malloc(keyLength));
            memset(m_keyBuffer, 0, keyLength);
        }

        OwnerV4PubSubType::~OwnerV4PubSubType()
        {
            if (m_keyBuffer != nullptr)
            {
                free(m_keyBuffer);
            }
        }

        bool OwnerV4PubSubType::serialize(
                void* data,
                SerializedPayload_t* payload)
        {
            OwnerV4* p_type = static_cast<OwnerV4*>(data);

            // Object that manages the raw buffer.
            eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->max_size);
            // Object that serializes the data.
            eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN, eprosima::fastcdr::Cdr::DDS_CDR);
            payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

            try
            {
                // Serialize encapsulation
                ser.serialize_encapsulation();
                // Serialize the object.
                p_type->serialize(ser);
            }
            catch (eprosima::fastcdr::exception::Exception& /*exception*/)
            {
                return false;
            }

            // Get the serialized length
            payload->length = static_cast<uint32_t>(ser.getSerializedDataLength());
            return true;
        }

        bool OwnerV4PubSubType::deserialize(
                SerializedPayload_t* payload,
                void* data)
        {
            try
            {
                // Convert DATA to pointer of your type
                OwnerV4* p_type = static_cast<OwnerV4*>(data);

                // Object that manages the raw buffer.
                eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->length);

                // Object that deserializes the data.
                eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN, eprosima::fastcdr::Cdr::DDS_CDR);

                // Deserialize encapsulation.
                deser.read_encapsulation();
                payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

                // Deserialize the object.
                p_type->deserialize(deser);
            }
            catch (eprosima::fastcdr::exception::Exception& /*exception*/)
            {
                return false;
            }

            return true;
        }

        std::function<uint32_t()> OwnerV4PubSubType::getSerializedSizeProvider(
                void* data)
        {
            return [data]() -> uint32_t
                   {
                       return static_cast<uint32_t>(type::getCdrSerializedSize(*static_cast<OwnerV4*>(data))) +
                              4u /*encapsulation*/;
                   };
        }

        void* OwnerV4PubSubType::createData()
        {
            return reinterpret_cast<void*>(new OwnerV4());
        }

        void OwnerV4PubSubType::deleteData(
                void* data)
        {
            delete(reinterpret_cast<OwnerV4*>(data));
        }

        bool OwnerV4PubSubType::getKey(
                void* data,
                InstanceHandle_t* handle,
                bool force_md5)
        {
            if (!m_isGetKeyDefined)
            {
                return false;
            }

            OwnerV4* p_type = static_cast<OwnerV4*>(data);

            // Object that manages the raw buffer.
            eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(m_keyBuffer),
                    OwnerV4::getKeyMaxCdrSerializedSize());

            // Object that serializes the data.
            eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS);
            p_type->serializeKey(ser);
            if (force_md5 || OwnerV4::getKeyMaxCdrSerializedSize() > 16)
            {
                m_md5.init();
                m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.getSerializedDataLength()));
                m_md5.finalize();
                for (uint8_t i = 0; i < 16; ++i)
                {
                    handle->value[i] = m_md5.digest[i];
                }
            }
            else
            {
                for (uint8_t i = 0; i < 16; ++i)
                {
                    handle->value[i] = m_keyBuffer[i];
                }
            }
            return true;
        }

        PetPubSubType::PetPubSubType()
        {
            setName("benchmark::idl::Pet");
            auto type_size = Pet::getMaxCdrSerializedSize();
            type_size += eprosima::fastcdr::Cdr::alignment(type_size, 4); /* possible submessage alignment */
            m_typeSize = static_cast<uint32_t>(type_size) + 4; /*encapsulation*/
            m_isGetKeyDefined = Pet::isKeyDefined();
            size_t keyLength = Pet::getKeyMaxCdrSerializedSize() > 16 ?
                    Pet::getKeyMaxCdrSerializedSize() : 16;
            m_keyBuffer = reinterpret_cast<unsigned char*>(malloc(keyLength));
            memset(m_keyBuffer, 0, keyLength);
        }

        PetPubSubType::~PetPubSubType()
        {
            if (m_keyBuffer != nullptr)
            {
                free(m_keyBuffer);
            }
        }

        bool PetPubSubType::serialize(
                void* data,
                SerializedPayload_t* payload)
        {
            Pet* p_type = static_cast<Pet*>(data);

            // Object that manages the raw buffer.
            eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->max_size);
            // Object that serializes the data.
            eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN, eprosima::fastcdr::Cdr::DDS_CDR);
            payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

            try
            {
                // Serialize encapsulation
                ser.serialize_encapsulation();
                // Serialize the object.
                p_type->serialize(ser);
            }
            catch (eprosima::fastcdr::exception::Exception& /*exception*/)
            {
                return false;
            }

            // Get the serialized length
            payload->length = static_cast<uint32_t>(ser.getSerializedDataLength());
            return true;
        }

        bool PetPubSubType::deserialize(
                SerializedPayload_t* payload,
                void* data)
        {
            try
            {
                // Convert DATA to pointer of your type
                Pet* p_type = static_cast<Pet*>(data);

                // Object that manages the raw buffer.
                eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->length);

                // Object that deserializes the data.
                eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN, eprosima::fastcdr::Cdr::DDS_CDR);

                // Deserialize encapsulation.
                deser.read_encapsulation();
                payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

                // Deserialize the object.
                p_type->deserialize(deser);
            }
            catch (eprosima::fastcdr::exception::Exception& /*exception*/)
            {
                return false;
            }

            return true;
        }

        std::function<uint32_t()> PetPubSubType::getSerializedSizeProvider(
                void* data)
        {
            return [data]() -> uint32_t
                   {
                       return static_cast<uint32_t>(type::getCdrSerializedSize(*static_cast<Pet*>(data))) +
                              4u /*encapsulation*/;
                   };
        }

        void* PetPubSubType::createData()
        {
            return reinterpret_cast<void*>(new Pet());
        }

        void PetPubSubType::deleteData(
                void* data)
        {
            delete(reinterpret_cast<Pet*>(data));
        }

        bool PetPubSubType::getKey(
                void* data,
                InstanceHandle_t* handle,
                bool force_md5)
        {
            if (!m_isGetKeyDefined)
            {
                return false;
            }

            Pet* p_type = static_cast<Pet*>(data);

            // Object that manages the raw buffer.
            eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(m_keyBuffer),
                    Pet::getKeyMaxCdrSerializedSize());

            // Object that serializes the data.
            eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS);
            p_type->serializeKey(ser);
            if (force_md5 || Pet::getKeyMaxCdrSerializedSize() > 16)
            {
                m_md5.init();
                m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.getSerializedDataLength()));
                m_md5.finalize();
                for (uint8_t i = 0; i < 16; ++i)
                {
                    handle->value[i] = m_md5.digest[i];
                }
            }
            else
            {
                for (uint8_t i = 0; i < 16; ++i)
                {
                    handle->value[i] = m_keyBuffer[i];
                }
            }
            return true;
        }


    } //End of namespace idl


} //End of namespace benchmark


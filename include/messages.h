#pragma once

#include <common.h>
#include <netmessages/netmessages.pb.h>

class CCLCMsg_ClientInfo {
    ::google::protobuf::uint32 pad;

    ::google::protobuf::UnknownFieldSet _unknown_fields_;

    ::google::protobuf::uint32 send_table_crc_;
    ::google::protobuf::uint32 server_count_;
    bool is_hltv_;
    bool is_replay_;
    ::google::protobuf::uint32 friends_id_;
    ::std::string* friends_name_;
    ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > custom_files_;

    mutable int _cached_size_;
    ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];
public:
    __forceinline void set_send_table_crc(::google::protobuf::uint32 value) {
        _has_bits_[0] |= 0x00000001u;
        send_table_crc_ = value;
    }
};

class CCLCMsg_Move {
    ::google::protobuf::uint32 pad;

    ::google::protobuf::UnknownFieldSet _unknown_fields_;

    ::google::protobuf::uint32 num_backup_commands_;
    ::google::protobuf::uint32 num_new_commands_;
    ::std::string* data_;

    mutable int _cached_size_;
    ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
public:
    __forceinline ::google::protobuf::uint32 num_backup_commands() const {
        return num_backup_commands_;
    }

    __forceinline ::google::protobuf::uint32 num_new_commands() const {
        return num_new_commands_;
    }

    __forceinline const ::std::string& data() const {
        return *data_;
    }

    __forceinline void set_data(const void* value, size_t size) {
        _has_bits_[0] |= 0x00000004u;

        if (data_ == &::google::protobuf::internal::kEmptyString)
            data_ = new ::std::string;

        data_->assign(reinterpret_cast<const char*>(value), size);
    }
};

class c_messages {
public:
    void fix_move_cmd(CCLCMsg_Move* message);
};

inline std::unique_ptr<c_messages> messages = std::make_unique<c_messages>();
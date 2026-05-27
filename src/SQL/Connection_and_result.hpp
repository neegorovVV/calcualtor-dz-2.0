#pragma once

#include <libpq-fe.h>

#include <memory>
#include <string>

class PostgresResult;

class PostgresConnection
{
   private:
    struct custom_deleter_con
    {
        void operator()(PGconn* ptr) const;
    };

    std::unique_ptr<PGconn, custom_deleter_con> ptr;

   public:
    PostgresConnection(const std::string& host, const std::string& port, const std::string& db_name,
                       const std::string& user, const std::string& password);
    ~PostgresConnection() = default;
    PostgresResult execute(const std::string& data);
};

class PostgresResult
{
   private:
    struct custom_deleter_res
    {
        void operator()(PGresult* ptr) const;
    };

    std::unique_ptr<PGresult, custom_deleter_res> res;

   public:
    explicit PostgresResult(PGresult* result);

    bool status_is_ok() const;
    int get_rows() const;
    int get_cols() const;
    const char* get_value(int row, int col) const;
};

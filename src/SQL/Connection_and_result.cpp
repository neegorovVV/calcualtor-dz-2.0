#include "Connection_and_result.hpp"

#include <stdexcept>

void PostgresConnection::custom_deleter_con::operator()(PGconn* ptr) const
{
    if (ptr)
        PQfinish(ptr);
}

PostgresConnection::PostgresConnection(const std::string& host, const std::string& port,
                                       const std::string& db_name, const std::string& user,
                                       const std::string& password)
{
    std::string conn_str = "host=" + host + " port=" + port + " dbname=" + db_name +
                           " user=" + user + " password=" + password;

    ptr.reset(PQconnectdb(conn_str.c_str()));

    if (PQstatus(ptr.get()) != CONNECTION_OK)
        throw std::runtime_error("CONNECTION FAILED: " + std::string(PQerrorMessage(ptr.get())));
}

PostgresResult PostgresConnection::execute(const std::string& data)
{
    PGresult* r = PQexec(ptr.get(), data.c_str());
    return PostgresResult(r);
}

void PostgresResult::custom_deleter_res::operator()(PGresult* ptr) const
{
    if (ptr)
        PQclear(ptr);
}

PostgresResult::PostgresResult(PGresult* result)
{
    res.reset(result);
}

int PostgresResult::get_rows() const
{
    return PQntuples(res.get());
}

int PostgresResult::get_cols() const
{
    return PQnfields(res.get());
}

const char* PostgresResult::get_value(int row, int col) const
{
    return PQgetvalue(res.get(), row, col);
}

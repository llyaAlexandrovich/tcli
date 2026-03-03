#pragma once



#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


// Type Dispatching.
namespace detail {
template <class... Fs>
struct overload;


template <class F>
struct overload<F> : public F {
    explicit overload(F f) : F(f) {
}
};


template <class F, class... Fs>
struct overload<F, Fs...> : public overload<F>, public overload<Fs...> {
    overload(F f, Fs... fs) : overload<F>(f), overload<Fs...>(fs...) {}
    using overload<F>::operator();
    using overload<Fs...>::operator();
};

}  // namespace detail


template <class... F>
auto overloaded(F... f) {
    return detail::overload<F...>(f...);
}
// ...Type Dispatching.


// Helpers.
namespace td_api = td::td_api;


using TdObject = td_api::object_ptr<td_api::Object>;
using TdAuthorizationState = td_api::object_ptr<td_api::AuthorizationState>;



// Prefixes.
// Prefix for chat name.
#define GROUP_CHAT_PREFIX L"✤"



// Consts.
// Max length of the full name to show as a preview.
#define MAX_FULL_NAME_LENGTH 15


// Max number of chat to load at once.
#define CHATS_TO_LOAD 20


// Default number of chats.
#define CHAT_LIST_LENGTH 40

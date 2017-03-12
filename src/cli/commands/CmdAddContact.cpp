/************************************************************
 *
 *                 OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, CLI, GUI
 *
 *       -- Anonymous Numbered Accounts.
 *       -- Untraceable Digital Cash.
 *       -- Triple-Signed Receipts.
 *       -- Cheques, Vouchers, Transfers, Inboxes.
 *       -- Basket Currencies, Markets, Payment Plans.
 *       -- Signed, XML, Ricardian-style Contracts.
 *       -- Scripted smart contracts.
 *
 *  EMAIL:
 *  fellowtraveler@opentransactions.org
 *
 *  WEBSITE:
 *  http://www.opentransactions.org/
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This Source Code Form is subject to the terms of the
 *   Mozilla Public License, v. 2.0. If a copy of the MPL
 *   was not distributed with this file, You can obtain one
 *   at http://mozilla.org/MPL/2.0/.
 *
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will
 *   be useful, but WITHOUT ANY WARRANTY; without even the
 *   implied warranty of MERCHANTABILITY or FITNESS FOR A
 *   PARTICULAR PURPOSE.  See the Mozilla Public License
 *   for more details.
 *
 ************************************************************/

#include "CmdAddContact.hpp"

#include <opentxs/core/Version.hpp>
#include <opentxs/api/Api.hpp>
#include <opentxs/api/OT.hpp>
#include <opentxs/client/OTME_too.hpp>

namespace opentxs
{
CmdAddContact::CmdAddContact()
{
    command = "addcontact";
    args[0] = "--hisnym <nym>";
    args[1] = "--label [<label>]";
    category = catOtherUsers;
    help = "Search for a nym's credentials";
}

int32_t CmdAddContact::runWithOptions()
{
    return run(getOption("hisnym"), getOption("label"));
}

int32_t CmdAddContact::run(
    const std::string& hisnym,
    const std::string& label)
{
    if (hisnym.empty()) {
        return -1;
    }

    const auto response = OT::App().API().OTME_TOO().AddContact(hisnym, label);

    if (response) {
        return 0;
    }

    return -1;
}
} // namespace opentxs

// Copyright (c) 2018 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "CmdRegisterContractNym.hpp"

#include <opentxs/opentxs.hpp>

#include <stdint.h>
#include <string>

using namespace opentxs;
using namespace std;

CmdRegisterContractNym::CmdRegisterContractNym()
{
    command = "registercontractnym";
    args[0] = "--server <server>";
    args[1] = "--mynym <nym>";
    args[2] = "--hisnym <nym>";
    category = catMisc;
    help = "Upload a nym's credentials to a server without registering.";
}

CmdRegisterContractNym::~CmdRegisterContractNym() {}

int32_t CmdRegisterContractNym::runWithOptions()
{
    return run(getOption("server"), getOption("mynym"), getOption("hisnym"));
}

int32_t CmdRegisterContractNym::run(string server, string mynym, string hisnym)
{
    if (!checkServer("server", server)) { return -1; }

    if (!checkNym("mynym", mynym)) { return -1; }

    if (!checkNym("hisnym", hisnym, true)) { return -1; }

    std::string response;
    {
        response = Opentxs::
                       Client()
                       .ServerAction()
                       .PublishNym(
                           Identifier::Factory(mynym),
                           Identifier::Factory(server),
                           Identifier::Factory(hisnym))
                       ->Run();
    }

    return processResponse(response, "register contract");
}

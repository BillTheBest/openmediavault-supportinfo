<?php
/**
 * This file is part of OpenMediaVault.
 *
 * @license		http://www.gnu.org/licenses/gpl.html GPL Version 3
 * @author		Volker Theile <volker.theile@openmediavault.org>
 * @author		Aaron Murray <aaron@omv-extras.org>
 * @copyright	Copyright (c) 2009-2013 Volker Theile 
 * @copyright	Copyright (c) 2013 Aaron Murray
 *
 * OpenMediaVault is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * OpenMediaVault is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenMediaVault. If not, see <http://www.gnu.org/licenses/>.
 */
require_once("openmediavault/object.inc");
require_once("openmediavault/error.inc");
require_once("openmediavault/module.inc");
require_once("openmediavault/rpcservice.inc");

class OMVRpcServiceSupportInfo extends OMVRpcServiceAbstract {
	/**
	 * Get the RPC service name.
	 */
	public function getName() {
		return "SupportInfo";
	}

	/**
	 * Initialize the RPC service.
	 */
	public function initialize() {
		$this->registerMethod("getSupportInfo");
	}

	public function getSupportInfo($params, $context) {
		// Validate the RPC caller context.
		$this->validateMethodContext($context, array( "role" => OMV_ROLE_ADMINISTRATOR ));
		
		$output = "";
		$result = "";

		OMVUtil::exec("sudo /usr/local/bin/omv-support.sh webgui", $result);
		$output = implode("\n", $result) . "\n";
		
		return $output;
	}
}

// Register the RPC service.
$rpcServiceMgr = &OMVRpcServiceMgr::getInstance();
$rpcServiceMgr->registerService(new OMVRpcServiceSupportInfo());
?>
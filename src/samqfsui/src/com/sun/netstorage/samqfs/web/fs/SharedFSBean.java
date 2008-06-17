/*
 *    SAM-QFS_notice_begin
 *
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at pkg/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at pkg/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 *    SAM-QFS_notice_end
 */

// ident        $Id: SharedFSBean.java,v 1.3 2008/06/17 16:04:27 ronaldso Exp $

package com.sun.netstorage.samqfs.web.fs;

import com.sun.data.provider.FieldKey;
import com.sun.data.provider.RowKey;
import com.sun.data.provider.TableDataProvider;
import com.sun.netstorage.samqfs.mgmt.SamFSException;
import com.sun.netstorage.samqfs.web.model.MemberInfo;
import com.sun.netstorage.samqfs.web.model.SamQFSAppModel;
import com.sun.netstorage.samqfs.web.model.SamQFSFactory;
import com.sun.netstorage.samqfs.web.model.SamQFSSystemModel;
import com.sun.netstorage.samqfs.web.model.SamQFSSystemSharedFSManager;
import com.sun.netstorage.samqfs.web.model.SharedHostInfo;
import com.sun.netstorage.samqfs.web.model.fs.FileSystem;
import com.sun.netstorage.samqfs.web.util.Constants;
import com.sun.netstorage.samqfs.web.util.JSFUtil;
import com.sun.netstorage.samqfs.web.util.SamUtil;
import com.sun.netstorage.samqfs.web.util.Select;
import com.sun.web.ui.component.DropDown;
import com.sun.web.ui.component.Hyperlink;
import com.sun.web.ui.component.TabSet;
import com.sun.web.ui.component.TableRowGroup;
import com.sun.web.ui.model.Option;
import com.sun.web.ui.model.OptionTitle;
import java.io.Serializable;
import javax.faces.event.ActionEvent;


public class SharedFSBean implements Serializable {

    /** Holds value of time loaded for each page. */
    protected String timeSummary = null;
    protected String timeClient = null;
    /** Holds value of tab set. */
    protected TabSet tabSet = null;
    /** Holds value of property jumpMenuSelectedOption. */
    protected String jumpMenuSelectedOption = null;
    /** Holds value of the file system type text. */
    protected String textType = null;
    /** Holds value of the file system mount point. */
    protected String textMountPoint = null;
    /** Holds value of the file system capacity. */
    protected String imageUsage = null;
    protected String textCapacity = null;
    /** Holds value of the file system high water mark. */
    protected String textHWM = null;
    /** Holds value of the file system archiving status. */
    protected String textArchiving = null;
    /** Holds value of the file system potential metadata server number. */
    protected String textPMDS = null;
    /** Holds value of the page title of clients section. */
    protected String titleClients = null;
    /** Holds value of the page title of storage nodes section. */
    protected String titleStorageNodes = null;
    /** Holds value of the client table row group. */
    protected TableRowGroup clientTableRowGroup = null;
    /** Holds value of the storage node table row group. */
    protected TableRowGroup snTableRowGroup = null;
    /** Holds value of the render value of storage nodes related components. */
    protected boolean showStorageNodes = false;
    /** Holds value of the render value of archive related components. */
    protected boolean showArchive = false;
    /** Holds value of the mount status of the file system. */
    protected boolean mounted = true;
    /** Holds value of alert info. */
    protected boolean alertRendered = false;
    protected String alertType = null;
    protected String alertDetail = null;
    protected String alertSummary = null;

    /** Hidden fields for javascript messages */
    protected String noMultipleOpMsg = null;
    protected String noneSelectedMsg = null;
    protected String confirmRemove = null;
    protected String confirmDisable = null;
    protected String confirmUnmount = null;
    protected String confirmUnmountFS = null;

    /** Holds table information in Client Summary Page. */
    protected TableRowGroup clientSummaryTableRowGroup = null;
    protected Select selectClient = new Select("clientTable");
    protected String clientTableSelectedOption = null;
    protected String clientTableFilterSelectedOption = null;

    private SharedFSTabBean tabBean = null;
    private SharedFSSummaryBean summaryBean = null;
    private SharedFSClientBean clientBean = null;
    private SharedFSStorageNodeBean snBean = null;


    public SharedFSBean() {
System.out.println("Entering SharedFSBean()!");
        this.tabBean = new SharedFSTabBean();
        this.summaryBean = new SharedFSSummaryBean();
        this.clientBean = new SharedFSClientBean();
        this.snBean = new SharedFSStorageNodeBean();

        // Call to the backend for first time page display
        getSummaryData();

        populateHiddenFields();
    }

    ////////////////////////////////////////////////////////////////////////////
    // Remote Calls

    private void getSummaryData() {
System.out.println("Calling to backend, getSummaryData()!");
        String fsName = getFSName();
        String serverName = JSFUtil.getServerName();

System.out.println("serverName: " + serverName);
System.out.println("fsName: " + fsName);

        timeSummary = Long.toString(System.currentTimeMillis());

        if (serverName != null) {
            try {
                SamQFSSystemSharedFSManager sharedFSManager =
                                                getSharedFSManager();
                MemberInfo [] infos = sharedFSManager.getSharedFSSummaryStatus(
                            serverName, fsName);
                FileSystem thisFS = getFileSystem();
                showArchive = thisFS.getArchivingType() == FileSystem.ARCHIVING;
                mounted = thisFS.getState() == FileSystem.MOUNTED;

                for (int i = 0; i < infos.length; i++) {
                    if (infos[i].isStorageNodes()) {
                        showStorageNodes = true;
                    }
                }

                summaryBean.populateSummary(infos, thisFS, showStorageNodes);

                // no error found
                this.alertRendered = false;

            } catch (SamFSException sfe) {
System.out.println("SamFSException caught!");
sfe.printStackTrace();
                SamUtil.processException(
                    sfe,
                    this.getClass(),
                    "getSummaryData",sfe.getMessage(),
                    serverName);
                setAlertInfo(
                    Constants.Alert.ERROR,
                    "L10N: Failed to populate summary info",
                    sfe.getMessage());
            }
        }
    }

    private void getClientData(short filter) {
        String fsName = getFSName();
        String serverName = JSFUtil.getServerName();

System.out.println("serverName: " + serverName);
System.out.println("fsName: " + fsName);

        timeClient = Long.toString(System.currentTimeMillis());

        if (serverName != null) {
            try {
                SamQFSSystemSharedFSManager sharedFSManager =
                                                getSharedFSManager();

                SharedHostInfo [] infos =
                    sharedFSManager.getSharedFSHosts(
                        serverName,
                        fsName,
                        SharedHostInfo.TYPE_MDS |
                        SharedHostInfo.TYPE_PMDS |
                        SharedHostInfo.TYPE_CLIENT,
                        filter);

                clientBean.populate(infos, showArchive);

                // no error found
                this.alertRendered = false;

            } catch (SamFSException sfe) {
System.out.println("SamFSException caught!");
sfe.printStackTrace();
                SamUtil.processException(
                    sfe,
                    this.getClass(),
                    "getClientData",sfe.getMessage(),
                    serverName);
                setAlertInfo(
                    Constants.Alert.ERROR,
                    "L10N: Failed to populate client info",
                    sfe.getMessage());
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Time when page is loaded
    public String getTimeSummary() {
        return timeSummary;
    }

    public void setTimeSummary(String timeSummary) {
        this.timeSummary = timeSummary;
    }

    public String getTimeClient() {
        return timeClient;
    }

    public void setTimeClient(String timeClient) {
        this.timeClient = timeClient;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Tab Set
    public TabSet getTabSet() {
System.out.println("getTabSet: " + showStorageNodes);
        this.tabSet = tabBean.getMyTabSet(showStorageNodes);
        return tabSet;
    }
    public void setTabSet(TabSet tabSet){
        this.tabSet = tabSet;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Breadcrumbs
    public Hyperlink [] getBreadCrumbsSummary(){
        return summaryBean.getBreadCrumbs();
    }

    public Hyperlink [] getBreadCrumbsClient(){
        return clientBean.getBreadCrumbs(getFSName());
    }

    public Hyperlink [] getBreadCrumbsStorageNode(){
        return snBean.getBreadCrumbs(getFSName());
    }

    ////////////////////////////////////////////////////////////////////////////
    // Alert

    public String getAlertDetail() {
        if (!alertRendered) {
            alertDetail = null;
        }
        return alertDetail;
    }

    public void setAlertDetail(String alertDetail) {
        this.alertDetail = alertDetail;
    }

    public String getAlertSummary() {
        if (!alertRendered) {
            alertSummary = null;
        }
        return alertSummary;
    }

    public void setAlertSummary(String alertSummary) {
        this.alertSummary = alertSummary;
    }

    public String getAlertType() {
        if (!alertRendered){
            alertType = Constants.Alert.INFO;
        }
        return alertType;
    }

    public void setAlertType(String alertType) {
        this.alertType = alertType;
    }

    public boolean isAlertRendered() {
System.out.println("Calling isAlertRendered: " + alertRendered);
        return alertRendered;
    }

    public void setAlertRendered(boolean alertRendered) {
        this.alertRendered = alertRendered;
    }

    public void setAlertInfo(String type, String summary, String detail) {
System.out.println("calling setAlertInfo!");
        alertRendered = true;
        this.alertType = type;
        this.alertSummary = summary;
        this.alertDetail = detail;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Property Sheet Components

    /** Return the array of jump menu options */
    public Option[] getJumpMenuOptions() {
        // Call to the backend
        getSummaryData();

System.out.println("Entering getJumpMenuOptions: mounted: " + mounted);
        return summaryBean.getJumpMenuOptions(showStorageNodes, mounted);
    }

    /** Get the value of property jumpMenuSelectedOption */
    public String getJumpMenuSelectedOption() {
        return this.jumpMenuSelectedOption;
    }

    /** Set the value of property jumpMenuSelectedOption */
    public void setJumpMenuSelectedOption(String jumpMenuSelectedOption) {
        this.jumpMenuSelectedOption = jumpMenuSelectedOption;
    }

    public void handleAddClients(ActionEvent event) {
        System.out.println("handleAddClients() called!");
    }

    public void handleAddStorageNodes(ActionEvent event) {
        System.out.println("handleAddStorageNodes() called!");
    }

    public void handleViewPolicies(ActionEvent event) {
        System.out.println("handleViewPolicies() called!");

        String params =
            Constants.PageSessionAttributes.SAMFS_SERVER_NAME
                 + "=" + JSFUtil.getServerName();

        params += "&" + Constants.PageSessionAttributes.FILE_SYSTEM_NAME
             + "=" + getFSName();

        // Check util/PageInfo.java, 36 is the number for SharedFSSummary
        params += "&" + Constants.SessionAttributes.PAGE_PATH
             + "=" + "2,36";
        JSFUtil.redirectPage("/fs/FSArchivePolicies", params);
    }

    public void handleJumpMenuSelection(ActionEvent event) {
System.out.println("handleJumpMenuSelection() called!");

        DropDown dropDown = (DropDown) event.getComponent();
        String selected = (String) dropDown.getSelected();
System.out.println("selected: " + selected);

        if ("editmo".equals(selected)){
            forwardToMountOptionsPage();
        } else if ("mount".equals(selected)) {
            executeCommand(true);
        } else if ("unmount".equals(selected)) {
            executeCommand(false);
        } else if ("removesn".equals(selected)) {
            forwardToSNPage();
        } else if ("removecn".equals(selected)) {
            forwardToClientPage((short)10);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Property Sheet Section ONE

    public String getTextArchiving() {
        return summaryBean.getTextArchiving();
    }

    public void setTextArchiving(String textArchiving) {
        this.textArchiving = textArchiving;
    }

    public String getTextPMDS() {
        return summaryBean.getTextPMDS();
    }

    public void setTextPMDS(String textPMDS) {
        this.textPMDS = textPMDS;
    }

    public String getTextHWM() {
        return summaryBean.getTextHWM();
    }

    public void setTextHWM(String textHWM) {
        this.textHWM = textHWM;
    }

    public String getTextCapacity() {
        return summaryBean.getTextCapacity();
    }

    public void setTextCapacity(String textCapacity) {
        this.textCapacity = textCapacity;
    }

    public String getImageUsage() {
        return summaryBean.getImageUsage();
    }

    public void setImageUsage(String imageUsage) {
        this.imageUsage = imageUsage;
    }

    public String getTextMountPoint() {
        return summaryBean.getTextMountPoint();
    }

    public void setTextMountPoint(String textMountPoint) {
        this.textMountPoint = textMountPoint;
    }

    public String getTextType() {
        return summaryBean.getTextType();
    }

    public void setTextType(String textType) {
        this.textType = textType;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Property Sheet Client Table

    public String getTitleClients() {
        return summaryBean.getTitleClients();
    }

    public void setTitleClients(String titleClients) {
        this.titleClients = titleClients;
    }

    public TableDataProvider getClientList() {
        return summaryBean.getClientList();
    }

    public TableRowGroup getClientTableRowGroup() {
        return clientTableRowGroup;
    }

    public void setClientTableRowGroup(TableRowGroup clientTableRowGroup) {
        this.clientTableRowGroup = clientTableRowGroup;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Property Sheet Storage Node Table

    public String getTitleStorageNodes() {
        return summaryBean.getTitleStorageNodes();
    }

    public void setTitleStorageNodes(String titleStorageNodes) {
        this.titleStorageNodes = titleStorageNodes;
    }

    public TableDataProvider getStorageNodeList() {
        return summaryBean.getStorageNodeList();
    }

    public TableRowGroup getSnTableRowGroup() {
        return snTableRowGroup;
    }

    public void setSnTableRowGroup(TableRowGroup snTableRowGroup) {
        this.snTableRowGroup = snTableRowGroup;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Helper methods
    private String getFSName() {
        return FSUtil.getFSName();
    }

    private FileSystem getFileSystem() throws SamFSException {
        String fsName = getFSName();
        SamQFSAppModel appModel = SamQFSFactory.getSamQFSAppModel();
        if (appModel == null) {
            throw new SamFSException("App model is null");
        }
        SamQFSSystemModel sysModel = SamUtil.getModel(JSFUtil.getServerName());
        return sysModel.getSamQFSSystemFSManager().getFileSystem(fsName);
    }

    private SamQFSSystemSharedFSManager getSharedFSManager()
        throws SamFSException {
        SamQFSAppModel appModel = SamQFSFactory.getSamQFSAppModel();

        if (appModel == null) {
            throw new SamFSException("App model is null");
        }

        SamQFSSystemSharedFSManager sharedFSManager =
                        appModel.getSamQFSSystemSharedFSManager();
        if (sharedFSManager == null) {
            throw new SamFSException("shared fs manager is null");
        }
        return sharedFSManager;
    }

    private void forwardToMountOptionsPage() {
        // TODO: NEED TO pass more attributes for shared fs
        String params =
            Constants.PageSessionAttributes.SAMFS_SERVER_NAME
                 + "=" + JSFUtil.getServerName();
        params += "&" + Constants.PageSessionAttributes.FILE_SYSTEM_NAME
             + "=" + getFSName();
        params += "&" + Constants.PageSessionAttributes.ARCHIVE_TYPE
             + "=" + (isShowArchive() ? FileSystem.ARCHIVING :
                                        FileSystem.NONARCHIVING);
        // TODO: Need to pass the correct attribute for shared fs
        /*
        params += "&" + Constants.SessionAttributes.MOUNT_PAGE_TYPE
             + "=" + (isShowArchive()? FSMountViewBean.TYPE_SHAREDQFS :
                                      FSMountViewBean.TYPE_SHAREDSAMQFS);
         */
        params += "&" + Constants.SessionAttributes.MOUNT_PAGE_TYPE
             + "=" + (isShowArchive()? FSMountViewBean.TYPE_UNSHAREDQFS :
                                      FSMountViewBean.TYPE_UNSHAREDSAMQFS);
        params += "&" + Constants.SessionAttributes.SHARED_CLIENT_HOST
             + "=" + "PUT_SOMETHING";
        // Check util/PageInfo.java, 36 is the number for SharedFSSummary
        params += "&" + Constants.SessionAttributes.PAGE_PATH
             + "=" + "2,36";

        JSFUtil.redirectPage("/fs/FSMount", params);
    }

    private void forwardToSNPage(){
        JSFUtil.redirectPage("/faces/jsp/fs/SharedFSStorageNode.jsp", "mode=5");
    }

    private void forwardToClientPage(short filter) {
        JSFUtil.redirectPage(
            "/faces/jsp/fs/SharedFSClient.jsp", "mode=" + filter);
    }

    private void executeCommand(boolean mount){
        try {
            FileSystem thisFS = getFileSystem();

            if (mount) {
                thisFS.mount();
            } else {
                thisFS.unmount();
            }
            setAlertInfo(
                Constants.Alert.INFO,
                mount ?
                    JSFUtil.getMessage("SharedFS.message.mount.ok",
                                       thisFS.getName()):
                    JSFUtil.getMessage("SharedFS.message.unmount.ok",
                                       thisFS.getName()),
                null);

        } catch (SamFSException samEx){
            SamUtil.processException(
                    samEx,
                    this.getClass(),
                    "executeCommand",samEx.getMessage(),
                    JSFUtil.getServerName());
            setAlertInfo(
                Constants.Alert.ERROR,
                mount ?
                    JSFUtil.getMessage("SharedFS.message.mount.failed",
                                       getFSName()):
                    JSFUtil.getMessage("SharedFS.message.unmount.failed",
                                       getFSName()),
                samEx.getMessage());
        }
    }

    private void populateHiddenFields() {
        noMultipleOpMsg = JSFUtil.getMessage("common.morethanoneselected");
        noneSelectedMsg = JSFUtil.getMessage("common.noneselected");
        confirmRemove = JSFUtil.getMessage("SharedFS.message.remove");
        confirmDisable = JSFUtil.getMessage("SharedFS.message.disable");
        confirmUnmount = JSFUtil.getMessage("SharedFS.message.unmount");
        confirmUnmountFS = JSFUtil.getMessage("SharedFS.message.unmountfs");
    }

    ////////////////////////////////////////////////////////////////////////////
    // Bean getters and setters
    public boolean isShowStorageNodes() {
        return showStorageNodes;
    }

    public void setShowStorageNodes(boolean showStorageNodes) {
        this.showStorageNodes = showStorageNodes;
    }

    public boolean isShowArchive() {
        return showArchive;
    }

    public void setShowArchive(boolean showArchive) {
        this.showArchive = showArchive;
    }

    public boolean isMounted() {
        return mounted;
    }

    public void setMounted(boolean mounted) {
        this.mounted = mounted;
    }

    public String getNoMultipleOpMsg() {
        return noMultipleOpMsg;
    }

    public void setNoMultipleOpMsg(String noMultipleOpMsg) {
        this.noMultipleOpMsg = noMultipleOpMsg;
    }

    public String getNoneSelectedMsg() {
        return noneSelectedMsg;
    }

    public void setNoneSelectedMsg(String noneSelectedMsg) {
        this.noneSelectedMsg = noneSelectedMsg;
    }

    public String getConfirmDisable() {
        return confirmDisable;
    }

    public void setConfirmDisable(String confirmDisable) {
        this.confirmDisable = confirmDisable;
    }

    public String getConfirmRemove() {
        return confirmRemove;
    }

    public void setConfirmRemove(String confirmRemove) {
        this.confirmRemove = confirmRemove;
    }

    public String getConfirmUnmount() {
        return confirmUnmount;
    }

    public void setConfirmUnmount(String confirmUnmount) {
        this.confirmUnmount = confirmUnmount;
    }

    public String getConfirmUnmountFS() {
        return confirmUnmountFS;
    }

    public void setConfirmUnmountFS(String confirmUnmountFS) {
        this.confirmUnmountFS = confirmUnmountFS;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Client Summary Page Methods (SharedFSClient.jsp)\
    public String getClientTableTitle() {
        return clientBean.getClientTableTitle();
    }

    public TableDataProvider getClientSummaryList() {
        getClientData(clientBean.getFilter());
        return clientBean.getClientList();
    }

    public TableRowGroup getClientSummaryTableRowGroup() {
        return clientSummaryTableRowGroup;
    }

    public void setClientSummaryTableRowGroup(
        TableRowGroup clientSummaryTableRowGroup) {
        this.clientSummaryTableRowGroup = clientSummaryTableRowGroup;
    }

    public void handleRemoveClient(ActionEvent event) {
        String [] selectedClients = getSelectedClients();
System.out.println("Entering handleRemoveClient: selected: " +
    selectedClients == null ? "null" : selectedClients.length);
        try {
            SamQFSSystemSharedFSManager sharedFSManager =
                                                getSharedFSManager();
            sharedFSManager.removeClients(getFSName(), selectedClients);

            setAlertInfo(
                Constants.Alert.INFO,
                JSFUtil.getMessage(
                    "SharedFS.message.removeclients.ok",
                    convertArrayToString(selectedClients)),
                null);
        } catch (SamFSException samEx) {
            setAlertInfo(
                Constants.Alert.ERROR,
                JSFUtil.getMessage(
                    "SharedFS.message.removeclients.failed",
                    convertArrayToString(selectedClients)),
                samEx.getMessage());
        }
    }

    public Select getSelectClient() {
        return selectClient;
    }

    public void setSelectClient(Select selectClient) {
        this.selectClient = selectClient;
    }

    public String getClientTableSelectedOption() {
        return clientTableSelectedOption;
    }

    public void setClientTableSelectedOption(String clientTableSelectedOption) {
        this.clientTableSelectedOption = clientTableSelectedOption;
    }

    public String getClientTableFilterSelectedOption() {
        this.clientTableFilterSelectedOption =
            clientBean.getClientTableFilterSelectedOption();
        return clientTableFilterSelectedOption;
    }

    public void setClientTableFilterSelectedOption(
        String clientTableFilterSelectedOption) {
        this.clientTableFilterSelectedOption = clientTableFilterSelectedOption;
    }

    /** Return the array of jump menu options */
    public Option[] getClientTableMenuOptions() {
        return clientBean.getJumpMenuOptions();
    }

    /** Return the array of filter menu options */
    public Option[] getClientTableFilterOptions() {
        return clientBean.getFilterMenuOptions();
    }

    public void handleTableMenuSelection(ActionEvent event) {
        String [] selectedClients = getSelectedClients();
System.out.println("Entering handleTableMenuSelection: selected: " +
    selectedClients == null ? "null" : selectedClients.length);

        DropDown dropDown = (DropDown) event.getComponent();
        String selected = (String) dropDown.getSelected();
System.out.println("handleTableMenuSelection() called: " + selected);

        if (clientBean.menuOptions[0][1].equals(selected)) {
            forwardToMountOptionsPage();
            return;
        }

        String message = "", errorMessage = "";

        try {
            SamQFSSystemSharedFSManager sharedFSManager =
                                                getSharedFSManager();
            // mount
            if (clientBean.menuOptions[1][1].equals(selected)) {
                sharedFSManager.mountClients(
                    JSFUtil.getServerName(), getFSName(), selectedClients);
                message = "SharedFS.message.mountclients.ok";
                errorMessage = "SharedFS.message.mountclients.failed";

            // unmount
            } else if (clientBean.menuOptions[2][1].equals(selected)) {
                sharedFSManager.unmountClients(
                    JSFUtil.getServerName(), getFSName(), selectedClients);
                message = "SharedFS.message.unmountclients.ok";
                errorMessage = "SharedFS.message.unmountclients.failed";

            // Enable Access
            } else if (clientBean.menuOptions[3][1].equals(selected)) {
                sharedFSManager.setClientState(
                        getFSName(), selectedClients, true);
                message = "SharedFS.message.enableclients.ok";
                errorMessage = "SharedFS.message.enableclients.failed";
            // Disable Access
            } else if (clientBean.menuOptions[4][1].equals(selected)) {
                sharedFSManager.setClientState(
                        getFSName(), selectedClients, false);
                message = "SharedFS.message.disableclients.ok";
                errorMessage = "SharedFS.message.disableclients.failed";
            }

            setAlertInfo(
                Constants.Alert.INFO,
                JSFUtil.getMessage(
                    message,
                    convertArrayToString(selectedClients)),
                null);
        } catch (SamFSException samEx) {
            setAlertInfo(
                Constants.Alert.ERROR,
                JSFUtil.getMessage(
                    errorMessage,
                    convertArrayToString(selectedClients)),
                samEx.getMessage());
        }
        
        // reset menu
        clientTableSelectedOption = OptionTitle.NONESELECTED;
    }

    public void handleFilterChange(ActionEvent event) {
        DropDown dropDown = (DropDown) event.getComponent();
        String selected = (String) dropDown.getSelected();
System.out.println("Entering handleFilterChange! selected:" + selected);
        forwardToClientPage(Short.parseShort(selected));
    }

    protected String [] getSelectedClients() {
        TableDataProvider provider = getClientSummaryList();
        RowKey [] rows = getClientSummaryTableRowGroup().getSelectedRowKeys();
        String [] selected = null;
        if (rows != null && rows.length >= 1) {
            selected = new String[rows.length];

            FieldKey field = provider.getFieldKey("name");
            for (int i = 0; i < rows.length; i++) {
                selected[i] = (String) provider.getValue(field, rows[i]);
            }
        }

        // safe to clear the selection
        getSelectClient().clear();
        return selected;
    }

    private String convertArrayToString(String [] inputArray) {
        if (inputArray == null ||inputArray.length == 0) {
            return "";
        }
        StringBuffer buf = new StringBuffer();
        for (int i = 0; i < inputArray.length; i++) {
            if (buf.length() > 0) {
                buf.append(",");
            }
            buf.append(inputArray[i]);
        }
        return buf.toString();
    }
}
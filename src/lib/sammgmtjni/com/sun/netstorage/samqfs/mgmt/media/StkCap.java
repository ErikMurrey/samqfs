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

// ident $

package com.sun.netstorage.samqfs.mgmt.media;

public class StkCap {

    private int acsNum;
    private int lsmNum;
    private int capNum;

    /**
     * private constructor
     */
    private StkCap(int acsNum, int lsmNum, int capNum) {

        this.acsNum = acsNum;
        this.lsmNum = lsmNum;
        this.capNum = capNum;

    }

    public int getAcsNum() { return acsNum; }
    public int getLsmNum() { return lsmNum; }
    public int getCapNum() { return capNum; }

    public String toString() {
        String s = "acsNum = " + acsNum +
                ", lsmNum = " + lsmNum +
                ", capNum = " + capNum;
        return s;
    }
}

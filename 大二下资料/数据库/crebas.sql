/*==============================================================*/
/* DBMS name:      SAP SQL Anywhere 17                          */
/* Created on:     2022/4/6 13:33:46                            */
/*==============================================================*/


if exists(select 1 from sys.sysforeignkey where role='FK_HOUSE_ÓµÓÐ_·¿ÎÝÄ¿Â¼') then
    alter table House
       delete foreign key FK_HOUSE_ÓµÓÐ_·¿ÎÝÄ¿Â¼
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_HOUSE_Ìá¹©_OWNER') then
    alter table House
       delete foreign key FK_HOUSE_Ìá¹©_OWNER
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_LEASEREC_×âÁÞ_HOUSE') then
    alter table LeaseRecord
       delete foreign key FK_LEASEREC_×âÁÞ_HOUSE
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_LEASEREC_×âÁÞ2_TENANT') then
    alter table LeaseRecord
       delete foreign key FK_LEASEREC_×âÁÞ2_TENANT
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_RESERVE_Ô¤¶©_HOUSE') then
    alter table Reserve
       delete foreign key FK_RESERVE_Ô¤¶©_HOUSE
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_RESERVE_Ô¤¶©2_TENANT') then
    alter table Reserve
       delete foreign key FK_RESERVE_Ô¤¶©2_TENANT
end if;

if exists(select 1 from sys.systable where table_name='View_1' and table_type='VIEW') then
   drop view View_1
end if;

drop index if exists House.Ìá¹©_FK;

drop index if exists House.ÓµÓÐ_FK;

drop index if exists House.·¿ÎÝ_PK;

drop table if exists House;

drop index if exists LeaseRecord.×âÁÞ2_FK;

drop index if exists LeaseRecord.×âÁÞ_FK;

drop index if exists LeaseRecord.×âÁÞ¼ÇÂ¼_PK;

drop table if exists LeaseRecord;

drop index if exists Owner.·¿¶«_PK;

drop table if exists Owner;

drop index if exists Reserve.Ô¤¶©2_FK;

drop index if exists Reserve.Ô¤¶©_FK;

drop index if exists Reserve.Ô¤¶©_PK;

drop table if exists Reserve;

drop index if exists Tenant.×âÁÞÕß_PK;

drop table if exists Tenant;

drop index if exists ·¿ÎÝÄ¿Â¼.·¿ÎÝÄ¿Â¼_PK;

drop table if exists ·¿ÎÝÄ¿Â¼;

/*==============================================================*/
/* Table: House                                                 */
/*==============================================================*/
create or replace table House 
(
   OwnerID              char(18)                       not null,
   HouseNumber          numeric(16)                    not null,
   HouseCode            numeric(16)                    null,
   HouseName            varchar(30)                    null,
   HouseArea            double                         null,
   HouseAddress         varchar(20)                    null,
   HousePrice           float(100)                     null,
   HouseUseTime         time                           null,
   HouseExist           smallint                       null,
   constraint PK_HOUSE primary key clustered (OwnerID, HouseNumber)
);

/*==============================================================*/
/* Index: ·¿ÎÝ_PK                                                 */
/*==============================================================*/
create unique clustered index ·¿ÎÝ_PK on House (
OwnerID ASC,
HouseNumber ASC
);

/*==============================================================*/
/* Index: ÓµÓÐ_FK                                                 */
/*==============================================================*/
create index ÓµÓÐ_FK on House (
HouseCode ASC
);

/*==============================================================*/
/* Index: Ìá¹©_FK                                                 */
/*==============================================================*/
create index Ìá¹©_FK on House (
OwnerID ASC
);

/*==============================================================*/
/* Table: LeaseRecord                                           */
/*==============================================================*/
create or replace table LeaseRecord 
(
   LeaseNumber          numeric(32)                    not null,
   OwnerID              char(18)                       null,
   HouseNumber          numeric(16)                    null,
   TenantID             char(18)                       null,
   HouseUseTime         timestamp                      null,
   constraint PK_LEASERECORD primary key clustered (LeaseNumber)
);

/*==============================================================*/
/* Index: ×âÁÞ¼ÇÂ¼_PK                                               */
/*==============================================================*/
create unique clustered index ×âÁÞ¼ÇÂ¼_PK on LeaseRecord (
LeaseNumber ASC
);

/*==============================================================*/
/* Index: ×âÁÞ_FK                                                 */
/*==============================================================*/
create index ×âÁÞ_FK on LeaseRecord (
OwnerID ASC,
HouseNumber ASC
);

/*==============================================================*/
/* Index: ×âÁÞ2_FK                                                */
/*==============================================================*/
create index ×âÁÞ2_FK on LeaseRecord (
TenantID ASC
);

/*==============================================================*/
/* Table: Owner                                                 */
/*==============================================================*/
create or replace table Owner 
(
   OwnerID              char(18)                       not null,
   OwnerName            char(4)                        null,
   OwnerAddress         varchar(30)                    null,
   OwnerPhone           varchar(11)                    null,
   constraint PK_OWNER primary key clustered (OwnerID)
);

/*==============================================================*/
/* Index: ·¿¶«_PK                                                 */
/*==============================================================*/
create unique clustered index ·¿¶«_PK on Owner (
OwnerID ASC
);

/*==============================================================*/
/* Table: Reserve                                               */
/*==============================================================*/
create or replace table Reserve 
(
   OwnerID              char(18)                       not null,
   HouseNumber          numeric(16)                    not null,
   TenantID             char(18)                       not null,
   constraint PK_RESERVE primary key clustered (OwnerID, HouseNumber, TenantID)
);

/*==============================================================*/
/* Index: Ô¤¶©_PK                                                 */
/*==============================================================*/
create unique clustered index Ô¤¶©_PK on Reserve (
OwnerID ASC,
HouseNumber ASC,
TenantID ASC
);

/*==============================================================*/
/* Index: Ô¤¶©_FK                                                 */
/*==============================================================*/
create index Ô¤¶©_FK on Reserve (
OwnerID ASC,
HouseNumber ASC
);

/*==============================================================*/
/* Index: Ô¤¶©2_FK                                                */
/*==============================================================*/
create index Ô¤¶©2_FK on Reserve (
TenantID ASC
);

/*==============================================================*/
/* Table: Tenant                                                */
/*==============================================================*/
create or replace table Tenant 
(
   TenantID             char(18)                       not null,
   TenantName           varchar(20)                    null,
   TenantGender         char(2)                        null,
   TenantPhone          varchar(11)                    null,
   constraint PK_TENANT primary key clustered (TenantID)
);

/*==============================================================*/
/* Index: ×âÁÞÕß_PK                                                */
/*==============================================================*/
create unique clustered index ×âÁÞÕß_PK on Tenant (
TenantID ASC
);

/*==============================================================*/
/* Table: ·¿ÎÝÄ¿Â¼                                                  */
/*==============================================================*/
create or replace table ·¿ÎÝÄ¿Â¼ 
(
   ·¿ÎÝ±àºÅ                 numeric(16)                    not null,
   ·¿ÎÝÃû³Æ                 varchar(30)                    null,
   ·¿ÎÝÀà±ð                 varchar(20)                    null,
   constraint PK_·¿ÎÝÄ¿Â¼ primary key clustered (·¿ÎÝ±àºÅ),
   constraint AK_·¿ÎÝ±àºÅ_·¿ÎÝÄ¿Â¼ unique (·¿ÎÝ±àºÅ)
);

/*==============================================================*/
/* Index: ·¿ÎÝÄ¿Â¼_PK                                               */
/*==============================================================*/
create unique clustered index ·¿ÎÝÄ¿Â¼_PK on ·¿ÎÝÄ¿Â¼ (
·¿ÎÝ±àºÅ ASC
);

/*==============================================================*/
/* View: View_1                                                 */
/*==============================================================*/
create view View_1  as
select
   House.OwnerID,
   House.HouseNumber,
   House.HouseCode,
   House.HouseName,
   House.HouseArea,
   House.HouseAddress,
   House.HousePrice,
   House.HouseUseTime,
   House.HouseExist
from
   House;

alter table House
   add constraint FK_HOUSE_ÓµÓÐ_·¿ÎÝÄ¿Â¼ foreign key (HouseCode)
      references ·¿ÎÝÄ¿Â¼ (·¿ÎÝ±àºÅ)
      on update restrict
      on delete restrict;

alter table House
   add constraint FK_HOUSE_Ìá¹©_OWNER foreign key (OwnerID)
      references Owner (OwnerID)
      on update restrict
      on delete restrict;

alter table LeaseRecord
   add constraint FK_LEASEREC_×âÁÞ_HOUSE foreign key (OwnerID, HouseNumber)
      references House (OwnerID, HouseNumber)
      on update restrict
      on delete restrict;

alter table LeaseRecord
   add constraint FK_LEASEREC_×âÁÞ2_TENANT foreign key (TenantID)
      references Tenant (TenantID)
      on update restrict
      on delete restrict;

alter table Reserve
   add constraint FK_RESERVE_Ô¤¶©_HOUSE foreign key (OwnerID, HouseNumber)
      references House (OwnerID, HouseNumber)
      on update restrict
      on delete restrict;

alter table Reserve
   add constraint FK_RESERVE_Ô¤¶©2_TENANT foreign key (TenantID)
      references Tenant (TenantID)
      on update restrict
      on delete restrict;


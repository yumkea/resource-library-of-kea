/*==============================================================*/
/* DBMS name:      SAP SQL Anywhere 17                          */
/* Created on:     2022/4/6 13:33:46                            */
/*==============================================================*/


if exists(select 1 from sys.sysforeignkey where role='FK_HOUSE_ӵ��_����Ŀ¼') then
    alter table House
       delete foreign key FK_HOUSE_ӵ��_����Ŀ¼
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_HOUSE_�ṩ_OWNER') then
    alter table House
       delete foreign key FK_HOUSE_�ṩ_OWNER
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_LEASEREC_����_HOUSE') then
    alter table LeaseRecord
       delete foreign key FK_LEASEREC_����_HOUSE
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_LEASEREC_����2_TENANT') then
    alter table LeaseRecord
       delete foreign key FK_LEASEREC_����2_TENANT
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_RESERVE_Ԥ��_HOUSE') then
    alter table Reserve
       delete foreign key FK_RESERVE_Ԥ��_HOUSE
end if;

if exists(select 1 from sys.sysforeignkey where role='FK_RESERVE_Ԥ��2_TENANT') then
    alter table Reserve
       delete foreign key FK_RESERVE_Ԥ��2_TENANT
end if;

if exists(select 1 from sys.systable where table_name='View_1' and table_type='VIEW') then
   drop view View_1
end if;

drop index if exists House.�ṩ_FK;

drop index if exists House.ӵ��_FK;

drop index if exists House.����_PK;

drop table if exists House;

drop index if exists LeaseRecord.����2_FK;

drop index if exists LeaseRecord.����_FK;

drop index if exists LeaseRecord.���޼�¼_PK;

drop table if exists LeaseRecord;

drop index if exists Owner.����_PK;

drop table if exists Owner;

drop index if exists Reserve.Ԥ��2_FK;

drop index if exists Reserve.Ԥ��_FK;

drop index if exists Reserve.Ԥ��_PK;

drop table if exists Reserve;

drop index if exists Tenant.������_PK;

drop table if exists Tenant;

drop index if exists ����Ŀ¼.����Ŀ¼_PK;

drop table if exists ����Ŀ¼;

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
/* Index: ����_PK                                                 */
/*==============================================================*/
create unique clustered index ����_PK on House (
OwnerID ASC,
HouseNumber ASC
);

/*==============================================================*/
/* Index: ӵ��_FK                                                 */
/*==============================================================*/
create index ӵ��_FK on House (
HouseCode ASC
);

/*==============================================================*/
/* Index: �ṩ_FK                                                 */
/*==============================================================*/
create index �ṩ_FK on House (
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
/* Index: ���޼�¼_PK                                               */
/*==============================================================*/
create unique clustered index ���޼�¼_PK on LeaseRecord (
LeaseNumber ASC
);

/*==============================================================*/
/* Index: ����_FK                                                 */
/*==============================================================*/
create index ����_FK on LeaseRecord (
OwnerID ASC,
HouseNumber ASC
);

/*==============================================================*/
/* Index: ����2_FK                                                */
/*==============================================================*/
create index ����2_FK on LeaseRecord (
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
/* Index: ����_PK                                                 */
/*==============================================================*/
create unique clustered index ����_PK on Owner (
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
/* Index: Ԥ��_PK                                                 */
/*==============================================================*/
create unique clustered index Ԥ��_PK on Reserve (
OwnerID ASC,
HouseNumber ASC,
TenantID ASC
);

/*==============================================================*/
/* Index: Ԥ��_FK                                                 */
/*==============================================================*/
create index Ԥ��_FK on Reserve (
OwnerID ASC,
HouseNumber ASC
);

/*==============================================================*/
/* Index: Ԥ��2_FK                                                */
/*==============================================================*/
create index Ԥ��2_FK on Reserve (
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
/* Index: ������_PK                                                */
/*==============================================================*/
create unique clustered index ������_PK on Tenant (
TenantID ASC
);

/*==============================================================*/
/* Table: ����Ŀ¼                                                  */
/*==============================================================*/
create or replace table ����Ŀ¼ 
(
   ���ݱ��                 numeric(16)                    not null,
   ��������                 varchar(30)                    null,
   �������                 varchar(20)                    null,
   constraint PK_����Ŀ¼ primary key clustered (���ݱ��),
   constraint AK_���ݱ��_����Ŀ¼ unique (���ݱ��)
);

/*==============================================================*/
/* Index: ����Ŀ¼_PK                                               */
/*==============================================================*/
create unique clustered index ����Ŀ¼_PK on ����Ŀ¼ (
���ݱ�� ASC
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
   add constraint FK_HOUSE_ӵ��_����Ŀ¼ foreign key (HouseCode)
      references ����Ŀ¼ (���ݱ��)
      on update restrict
      on delete restrict;

alter table House
   add constraint FK_HOUSE_�ṩ_OWNER foreign key (OwnerID)
      references Owner (OwnerID)
      on update restrict
      on delete restrict;

alter table LeaseRecord
   add constraint FK_LEASEREC_����_HOUSE foreign key (OwnerID, HouseNumber)
      references House (OwnerID, HouseNumber)
      on update restrict
      on delete restrict;

alter table LeaseRecord
   add constraint FK_LEASEREC_����2_TENANT foreign key (TenantID)
      references Tenant (TenantID)
      on update restrict
      on delete restrict;

alter table Reserve
   add constraint FK_RESERVE_Ԥ��_HOUSE foreign key (OwnerID, HouseNumber)
      references House (OwnerID, HouseNumber)
      on update restrict
      on delete restrict;

alter table Reserve
   add constraint FK_RESERVE_Ԥ��2_TENANT foreign key (TenantID)
      references Tenant (TenantID)
      on update restrict
      on delete restrict;


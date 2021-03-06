function [Props,AsgnVals] = pnames(RespObj,flag)
%PNAMES  All public properties and their assignable values
%
%   [PROPS,ASGNVALS] = PNAMES(RESPOBJ,'true')  returns the list PROPS 
%   (in a cell vector) of public properties of the object RESPOBJ , as well
%   as the assignable values ASGNVALS for these properties (a cell vector
%   of strings).  PROPS contains the true case-sensitive property names.
%   These include the public properties of RESPOBJ's parent(s).
%
%   [PROPS,ASGNVALS] = PNAMES(RESPOBJ,'lower')  returns lowercase property
%   names.  This helps speed up name matching in GET and SET.
%
%   See also  GET, SET.
% $Revision: 1.2 $

%   Author(s): P. Gahinet, 7-8-97
%	 Karen D. Gondoly, 1-2-98 (Modified for Response Objects) 
%   Copyright (c) 1986-98 by The MathWorks, Inc.

flag=lower(flag);

% Pole-zero Map (pzresp) specific public properties
Props= {'GridLines';
   'GridType';
   'Poles';
   'Zeros'};

if strcmp(flag,'lower'),
   Props = lower(Props);
end

% Construct outputs
if nargout<=1,
   % Only property names needed: add parent properties
   Props = [Props ; pnames(RespObj.response,flag)];
   
else
   % Also return values
   AsgnVals = {'vector of line handles'; ...
      	'string ({''sgrid''},''zgrid'',''square'')'; ...
      	'cell array of pole locations'; ...   
         'cell array of zerolocations'};
   
   % Add parent properties and their admissible values
   [RespProps,RespVals] = pnames(RespObj.response,flag);
   Props = [Props ; RespProps];
   AsgnVals = [AsgnVals ; RespVals];
   
end

% end pzresp/pnames.m

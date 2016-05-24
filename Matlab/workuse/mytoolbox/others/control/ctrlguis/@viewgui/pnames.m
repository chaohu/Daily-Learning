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
% $Revision: 1.6 $

%   Author(s): P. Gahinet, 7-8-97
%	 Karen D. Gondoly, 1-2-98 (Modified for Response Objects) 
%   Copyright (c) 1986-98 by The MathWorks, Inc.

%---Make sure there are two input arguments.
error(nargchk(2,2,nargin));

flag=lower(flag);

% Response Objec properties
Props = {'Parent';
   'ArrayPlotVariable';
   'AxesPosition';
   'BackgroundAxes';
   'ChannelPlotVariable';
   'ColorOrder';
   'Configuration';
   'ConfigurationWindow';
   'FigureMenu';
   'FrequencyData';	
   'FrequencyUnits';
   'FrequencyVector';
   'FrequencyVectorMode';
   'Handle';
   'InitialCondition';
   'InputPlotVariable';
   'InputSignal';
   'LineStyleOrder';
   'LineStylePreferences';
   'MagnitudeUnits';
   'MarkerOrder';
   'OutputPlotVariable';
   'PhaseUnits';
   'PlotStrings';
   'PlotTypeOrder';
   'ResponsePreferences';
   'RiseTimeLimits';
   'SettlingTimeThreshold';
   'SingularValueType';
   'Systems';
   'SystemNames';
   'SystemPlotVariable';
   'TimeData';
   'TimeVector';
   'TimeVectorMode';
   'UIContextMenu';
   'Visible';
   'Ylims';
   'YlimMode';
   'InitializeViewer';
   'StatusText';
   'StatusFrame'};

if strcmp(flag,'lower');
   Props = lower(Props);
end

% Also return values if needed
if nargout>1,
   AsgnVals = {'object that opened the viewer'; ...
               'plot style for different array elements(''color'',''marker'',''linestyle'',{''none''})'; ...
		         'cell array of axes positions for different configurations'; ...
               'vector of axes handles'; ...
               'plot style for different channels (''color'',''marker'',''linestyle'',{''none''})'; ...
               'character array'; ...
               'axes configuration number (1-6)'; ...
               'toggle visibility of configuration window'; ...
               'handles of LTI Viewer menus'; ...
               'indices of FRD objects in Systems list'; ...
               'string (''Hz'', {''rad/s''})'; ...
               'frequency vector'; ...
               'string ({''auto''},''manual'',''hold'')'; ...
               'figure handle'; ...
               'initial state conditions for INITIAL plot type'; ...
               'plot style for different inputs (''color'',''marker'',''linestyle'',{''none''})'; ...
               'input signal for LSIM plot type'; ...
            	'character array'; ...
               'handle of Linestyle Preference window'; ...
		         'string (''absolute'',{''decibels''},''logrithmic'')'; ...
               'character array'; ...
               'plot style for different outputs (''color'',''marker'',''linestyle'',{''none''})'; ...
		         'string ({''degrees''}, ''radians'')'; ...
         	   'cell array of plot style strings';...
               'cell array of plot type order'; ...
               'handle of Response Preference window'; ...
               '1x2 vector of limits for rise time calculation';...
               'percent limit for settling time calculation';...
               'type index for modified singular value plots'; ...
               'cell array of LTI objects'; ...
               'cell array of system names'; ...
               'plot style for different systems ({''color''},''marker'',''linestyle'',''none'')'; ...
               'structured array of user-defined time domain data'; ...
               'time vector'; ...
               'string ({''auto''},''manual'')'; ...
               'vector of UIcontextMenu handles'; ...
               'cell array of global visibility strings ({''on''},''off'')'; ...
               '2x1 vector of common Y-axis limits'; ...
               'string ({''auto''},''manual'')'; ...
               'Structured array of initialization data'; ...
               'Handle of the Status Bar Text'; ...
            	'Handle of the Status Bar Frame'};
end

% end viewgui/pnames.m
function y = rectpuls(t,Tw)
%RECTPULS Sampled aperiodic rectangle generator.
%   RECTPULS(T) generates samples of a continuous, aperiodic,
%   unity-height rectangle at the points specified in array T, centered
%   about T=0.  By default, the rectangle has width 1.  Note that the
%   interval of non-zero amplitude is defined to be open on the right,
%   i.e., RECTPULS(-0.5)=1 while RECTPULS(0.5)=0.
%
%   RECTPULS(T,W) generates a rectangle of width W.
%
%   See also GAUSPULS, TRIPULS, PULSTRAN.

%   Author(s): D. Orofino, 4/96
%   Copyright (c) 1988-98 by The MathWorks, Inc.
%       $Revision: 1.1 $

error(nargchk(1,2,nargin));
if nargin<2, Tw=1;   end

% Returns unity in interval [-Tw/2,+Tw/2) (right side of interval is open)
y = abs(t)<Tw/2;
y(find(t==-Tw/2)) = 1.0;

% end of rectpuls.m